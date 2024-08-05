#include "pch.h"
#include "MySceneStage3.h"
using namespace MyProject;

void MySceneStage3::Init()
{
	mCurrentButton = 0;
	mTileMap.LoadScript(L"../data/Image/Tile/stage3.tile");
	mPauseBackground.SetColor({ 0.f, 0.f, 0.f, 1.f });
	mPauseBackground->SetScale({ 160.f, 90.f });
	mPauseBackground.SetShaderKey(L"BackgroundPause.hlsl");

	mButtons[0]->SetLocation({ 0.f, 11.f });
	mButtons[1]->SetLocation({ 0.f, 0.f });
	mButtons[2]->SetLocation({ 0.f, -11.f });
	mButtons[0].SetText(L"계속 하기");
	mButtons[1].SetText(L"다시 시작");
	mButtons[2].SetText(L"메뉴로 나가기");
	mButtons[mCurrentButton].SetCurrentState(SelectState::ACTIVE);

}

void MySceneStage3::Update(float _deltaTime)
{
	if (mInput.GetCurrentKeyState(VK_ESCAPE) == KeyState::KEY_DOWN)
	{
		if (isPause)
		{
			isPause = false;
		}
		else
		{
			mManager.mSound[L"pause.wav"]->Play();
			isPause = true;
		}
	}

	if (mInput.GetCurrentKeyState(VK_UP) == KeyState::KEY_DOWN)
	{
		if (isPause)
		{
			mManager.mSound[L"menu-change.wav"]->Play();
			mButtons[mCurrentButton].SetCurrentState(SelectState::DEFAULT);
			mCurrentButton--;
			mCurrentButton = (mCurrentButton + 3) % 3;
			mButtons[mCurrentButton].SetCurrentState(SelectState::ACTIVE);
		}
	}
	if (mInput.GetCurrentKeyState(VK_DOWN) == KeyState::KEY_DOWN)
	{
		if (isPause)
		{
			mManager.mSound[L"menu-change.wav"]->Play();
			mButtons[mCurrentButton].SetCurrentState(SelectState::DEFAULT);
			mCurrentButton++;
			mCurrentButton %= 3;
			mButtons[mCurrentButton].SetCurrentState(SelectState::ACTIVE);
		}
	}

	if (mInput.GetCurrentKeyState(VK_RETURN) == KeyState::KEY_DOWN ||
		mInput.GetCurrentKeyState(0x5A) == KeyState::KEY_DOWN ||
		mInput.GetCurrentKeyState(0x58) == KeyState::KEY_DOWN)
	{
		if (isPause)
		{
			if (mCurrentButton == 0)
			{
				mManager.mSound[L"menu-select.wav"]->Play();
				isPause = false;
				//mManager.mSound[L"title-start.wav"]->Play();
				//mSceneManager.SetCurrentScene(L"STAGE");
			}
			else if (mCurrentButton == 1)
			{
				mManager.mSound[L"menu-select.wav"]->Play();
				Reset();

			}
			else if (mCurrentButton == 2)
			{
				mManager.mSound[L"menu-select.wav"]->Play();
				mSceneManager.SetCurrentScene(L"STAGE");
			}
		}
	}

	mObjManager.Update(_deltaTime);

	for (int i = 0; i < 3; i++)
		mButtons[i].Update(_deltaTime);
	//mTileMap.ProcessCollision(mPlayer);
}

void MySceneStage3::Reset()
{
	mObjManager.ClearObject();
	Start();
}

void MySceneStage3::Start()
{
	auto player = std::make_unique<MyPlayer>();
	auto woodBox1 = std::make_unique<MyWoodBox>();
	auto woodBox2 = std::make_unique<MyWoodBox>();
	auto ruby  = std::make_unique<MyRuby>(mSceneManager);

	(*player)->SetLocation({ 0.f, -30.f });
	(*woodBox1)->SetLocation({ 2.5f, -28.f });
	(*woodBox2)->SetLocation({ 1.5f, -36.f });
	(*ruby)->SetLocation({ -38.f, 19.f });

	mButtons[mCurrentButton].SetCurrentState(SelectState::DEFAULT);
	mCurrentButton = 0;
	mButtons[mCurrentButton].SetCurrentState(SelectState::ACTIVE);
	isPause = false;

	mObjManager.AddObject(std::move(player));
	mObjManager.AddObject(std::move(woodBox1));
	mObjManager.AddObject(std::move(woodBox2));
	mObjManager.AddObject(std::move(ruby));

	mObjManager.SetTileManager(&mTileMap);

	mManager.mSound[L"theme.ogg"]->Stop();
	if(!mManager.mSound[L"ashrams.ogg"]->IsPlaying())
		mManager.mSound[L"ashrams.ogg"]->Play(true);
}

void MySceneStage3::End()
{
	mObjManager.ClearObject();
}
