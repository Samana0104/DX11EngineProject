#include "pch.h"
#include "MyTile.h"
using namespace MyProject;

MyTile::MyTile()
{
	SetObjectCode(ObjectCode::TILE);
}

void MyTile::SetUVRect(const RECT_F _uv)
{
	mUV = _uv;
}

void MyTile::SetRow(const int _row)
{
	mRow = _row;
}

void MyTile::SetColumn(const int _column)
{
	mColumn = _column;
}

int MyTile::GetRow() const
{
	return mRow;
}

int MyTile::GetColumn() const
{
	return mColumn;
}

const RECT_F& MyTile::GetUVRect() const
{
	return mUV;
}

void MyTile::OnCollision(RECT_F& _self, RECT_F& _target, MyActor& _targetObj)
{
	// 고정형 블럭
	return;
}

void MyTile::Update(const float _deltaTime)
{
	
}

void MyTile::Render()
{
	vec2 imageSize = mManager.mTexture[mTextureKey]->GetTextureSizeVec2();
	mManager.mShader[mShaderKey]->SetUpConfiguration();
	mManager.mTexture[mTextureKey]->Render();
	mManager.mMesh[mMeshKey]->SetUVVertexAsRect(mUV, imageSize);
	mManager.mMesh[mMeshKey]->Draw(mTransform.GetModelMat(), mColor);
}
