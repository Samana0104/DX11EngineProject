#include "pch.h"
#include "MyTileManager.h"
using namespace MyProject;

MyTileManager::MyTileManager():
	mBackground(std::make_shared<MyTile>())
{
}

bool MyTileManager::LoadScript(const wstringV _filePath)
{
	FILE* fp_src = nullptr;

	_wfopen_s(&fp_src, _filePath.data(), _T("rt"));

	if (fp_src == nullptr)
		return false;

//---------------------------

	TCHAR buffer[256] = { 0 };
	TCHAR buffer1[256] = { 0 };
	TCHAR buffer2[256] = { 0 };
	WCHAR tileKey[2] = { 0 };
	wstringV converter;
	int readFrame = 0;
	int isCollision;
	RECT_F mUV;

	_fgetts(buffer, _countof(buffer), fp_src); // #Background
	_fgetts(buffer, _countof(buffer), fp_src); // #Background
	_stscanf_s(buffer, L"%f %f %f %f %s %s",
			&mUV.left,
			&mUV.top,
			&mUV.right,
			&mUV.bottom,
			buffer1,
			(unsigned int)_countof(buffer1),
			buffer2,
			(unsigned int)_countof(buffer2)
		);

		mBackground->SetUVRect(mUV);
		mBackground->SetTextureKey(buffer1);
		mBackground->SetShaderKey(buffer2);

//----------------------------------------------------------

	_fgetts(buffer, _countof(buffer), fp_src); // #BLOCK
// ---------------------------
	_fgetts(buffer, _countof(buffer), fp_src);
	_stscanf_s(buffer, L"%d", &readFrame);

	for (int iFrame = 0; iFrame < readFrame; iFrame++)
	{
		auto tile = std::make_shared<MyTile>();

		_fgetts(buffer, _countof(buffer), fp_src);
		_stscanf_s(buffer, L"%s %d%f%f%f%f %s%s",
			tileKey,
			(unsigned int)_countof(tileKey),
			&isCollision,
			&mUV.left,
			&mUV.top,
			&mUV.right,
			&mUV.bottom,
			buffer1,
			(unsigned int)_countof(buffer1),
			buffer2,
			(unsigned int)_countof(buffer2)
		);

		tile->SetUVRect(mUV);
		tile->SetTextureKey(buffer1);
		tile->SetShaderKey(buffer2);
		tile->GetCollisionComponent().SetCollisionable(static_cast<bool>(isCollision));
		
		mTiles.insert(std::make_pair(tileKey[0], tile));
	}

//-----------------------------------------------------
	_fgetts(buffer, _countof(buffer), fp_src); // #BLOCK

	while (true)
	{
		_fgetts(buffer, _countof(buffer), fp_src); 
		_stscanf_s(buffer, L"%s", buffer1, (unsigned int)_countof(buffer1));

		converter = buffer1;
		
		if (converter.compare(L"#end") == 0)
			break;
		
		for (int i = 0; i < converter.size(); i++)
		{
			if (mTiles.contains(converter[i]))
			{
				auto tile = std::make_shared<MyTile>();
				tile->SetTextureKey(mTiles[converter[i]]->GetTextureKey());
				tile->SetUVRect(mTiles[converter[i]]->GetUVRect());
				tile->SetShaderKey(mTiles[converter[i]]->GetShaderKey());
				tile->GetCollisionComponent().SetCollisionable(
					mTiles[converter[i]]->GetCollisionComponent().IsCollisionable());
				tile->SetRow(i);
				tile->SetColumn(mColumns);

				if (tile->GetCollisionComponent().IsCollisionable())
					mCollisions.push_back(tile);
				mTileMap.emplace_back(std::move(tile));
			}
		}
		mColumns++;
		mRows = static_cast<int>(converter.size());
	}

	fclose(fp_src);

	mIsScriptLoaded = true;

	SetSize({ 162.f, 92.f });
	SetPosition({ 0.f, 0.f });
	return true;
}

void MyTileManager::SetPosition(const vec2 _pos)
{
	if (!mIsScriptLoaded)
	{
		MessageBoxA(NULL, "Script Is Not Loaded","[MyTileManager error]", MB_OK);
		return;
	}

	for (auto& tile : mTileMap)
	{
		(*tile)->SetLocation(
			{
				_pos.x + tile->GetRow() * mTileSize.x - mSize.x * 0.5f + mTileSize.x*0.5f,
				_pos.y + -tile->GetColumn() * mTileSize.y + mSize.y * 0.5f - mTileSize.y*0.5f
			});
	}

	mPosition = _pos;
}

void MyTileManager::SetSize(const vec2 _size)
{
	if (!mIsScriptLoaded)
	{
		MessageBoxA(NULL, "Script Is Not Loaded","[MyTileManager error]", MB_OK);
		return;
	}

	float widthPerTile = _size.x / static_cast<float>(mRows);
	float heightPerTile = _size.y / static_cast<float>(mColumns);

	for (auto& tile : mTileMap)
	{
		(*tile)->SetScale({ widthPerTile, heightPerTile });
		tile->GetCollisionComponent().ResizeCollisionArea();
	}

	(*mBackground)->SetScale({ widthPerTile * 2.5f, heightPerTile * 2.5f });
	mSize = _size;
	mTileSize = { widthPerTile, heightPerTile };
}

const vec2& MyTileManager::GetTileSize() const
{
	return mTileSize;
}

void MyTileManager::ProcessCollision(MyActor& _actor)
{
	for (auto& tile : mCollisions)
		tile->GetCollisionComponent().IsCollisionWithEvent(
			_actor.GetCollisionComponent());
}

void MyTileManager::Render()
{
	// background size = 2 * tile size
	for (float i = 0; i<mColumns+0.5f; i += 2.5f)
	{
		for (float j = 0; j < mRows+0.5f; j += 2.5f)
		{
			(*mBackground)->SetLocation(
			{
				j * mTileSize.x - mSize.x * 0.5f,
				-i * mTileSize.y + mSize.y * 0.5f
			});

			mBackground->Render();
		}
	}

	for (auto& tile : mTileMap)
		tile->Render();
}


