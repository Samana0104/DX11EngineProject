#include "pch.h"
#include "MySceneStage.h"
using namespace MyProject;

void MySceneStage::Init()
{
	mCurrentButton = 0;
	mBackground->SetScale({ 160.f, 90.f });
	mBackground2->SetScale({ 160.f, 90.f });
	mBackground.SetColor({ 0.f, 0.f, 0.f, 1.f });
	mBackground2.SetColor({ 0.f, 0.f, 1.f, 1.f });
	mButtons[0].SetText(L"돌아가기");
	mButtons[0]->AddLocation({ -45.f, 0.f });
	mButtons[1].SetText(L"입구");
	mButtons[1]->AddLocation({ -15.f, 0.f });
	mButtons[2].SetText(L"열쇠");
	mButtons[2]->AddLocation({ 15.f, 0.f });
	mButtons[3].SetText(L"상자");
	mButtons[3]->AddLocation({ 45.f, 0.f });

	for(int i=0; i<4; i++)
		mButtons[i].SetImage(L"SmallBox_Open.png");

	mBackground2.SetShaderKey(L"Background.hlsl");
	mButtons[mCurrentButton].SetCurrentState(SelectState::ACTIVE);
}

void MySceneStage::Update(float _deltaTime)
{
	if (mInput.GetCurrentKeyState(VK_LEFT) == KeyState::KEY_DOWN)
	{
		mManager.mSound[L"menu-change.wav"]->Play();
		mButtons[mCurrentButton].SetCurrentState(SelectState::DEFAULT);
		mCurrentButton--;
		mCurrentButton = (mCurrentButton + 4) % 4;
		mButtons[mCurrentButton].SetCurrentState(SelectState::ACTIVE);
	}
	if (mInput.GetCurrentKeyState(VK_RIGHT) == KeyState::KEY_DOWN)
	{
		mManager.mSound[L"menu-change.wav"]->Play();
		mButtons[mCurrentButton].SetCurrentState(SelectState::DEFAULT);
		mCurrentButton++;
		mCurrentButton %= 4;
		mButtons[mCurrentButton].SetCurrentState(SelectState::ACTIVE);
	}

	if (mInput.GetCurrentKeyState(VK_RETURN) == KeyState::KEY_DOWN ||
		mInput.GetCurrentKeyState(0x5A) == KeyState::KEY_DOWN ||
		mInput.GetCurrentKeyState(0x58) == KeyState::KEY_DOWN)
	{
		if (mCurrentButton == 0)
		{
			mManager.mSound[L"chest-enter.wav"]->Play();
			mSceneManager.SetCurrentScene(L"LOBBY");
		}
		else if (mCurrentButton == 1)
		{
			mManager.mSound[L"chest-enter.wav"]->Play();
			mSceneManager.SetCurrentScene(L"STAGE1");
		}
		else if(mCurrentButton == 2)
		{
			mManager.mSound[L"chest-enter.wav"]->Play();
			mSceneManager.SetCurrentScene(L"STAGE2");
		}
		else if(mCurrentButton == 3)
		{
			mManager.mSound[L"chest-enter.wav"]->Play();
			mSceneManager.SetCurrentScene(L"STAGE3");
		}
	}

	for (int i = 0; i < 4; i++)
		mButtons[i].Update(_deltaTime);
}

void MySceneStage::Render()
{
	mBackground.Render();
	mBackground2.Render();
	for (int i = 0; i < 4; i++)
		mButtons[i].Render();
}

void MySceneStage::Release()
{
	mManager.mSound[L"ashrams.ogg"]->Stop();
}

void MySceneStage::Reset()
{
}

void MySceneStage::Start()
{
}

void MySceneStage::End()
{
}
