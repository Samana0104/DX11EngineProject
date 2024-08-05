#include "pch.h"
#include "MySceneLobby.h"
using namespace MyProject;

void MySceneLobby::Init()
{
	mCurrentButton = 0;
	mTitle.SetTextureKey(L"title1.png");
	mTitle->SetScale({ 135.f, 25.f });
	mTitle->SetLocation({ 0.f, 17.f });
	mBackground.SetImageScale();
	mBackground.SetColor({ 0.f, 0.f, 0.f, 1.f });
	mButtons[0]->SetLocation({ 0.f, -7.f });
	mButtons[1]->SetLocation({ 0.f, -17.f });
	mButtons[2]->SetLocation({ 0.f, -27.f });
	mButtons[0].SetText(L"시작");
	mButtons[1].SetText(L"설정");
	mButtons[2].SetText(L"나가기");
	mButtons[mCurrentButton].SetCurrentState(SelectState::ACTIVE);
	mManager.mSound[L"menu-change.wav"]->VolumneDown(0.3f);
}

void MySceneLobby::Update(float _deltaTime)
{
	if (mInput.GetCurrentKeyState(VK_UP) == KeyState::KEY_DOWN)
	{
		mManager.mSound[L"menu-change.wav"]->Play();
		mButtons[mCurrentButton].SetCurrentState(SelectState::DEFAULT);
		mCurrentButton--;
		mCurrentButton = (mCurrentButton + 3) % 3;
		mButtons[mCurrentButton].SetCurrentState(SelectState::ACTIVE);
	}
	if (mInput.GetCurrentKeyState(VK_DOWN) == KeyState::KEY_DOWN)
	{
		mManager.mSound[L"menu-change.wav"]->Play();
		mButtons[mCurrentButton].SetCurrentState(SelectState::DEFAULT);
		mCurrentButton++;
		mCurrentButton %= 3;
		mButtons[mCurrentButton].SetCurrentState(SelectState::ACTIVE);
	}

	if (mInput.GetCurrentKeyState(VK_RETURN) == KeyState::KEY_DOWN ||
		mInput.GetCurrentKeyState(0x5A) == KeyState::KEY_DOWN ||
		mInput.GetCurrentKeyState(0x58) == KeyState::KEY_DOWN)
	{
		if (mCurrentButton == 0)
		{
			mManager.mSound[L"title-start.wav"]->Play();
			mSceneManager.SetCurrentScene(L"STAGE");
		}
		else if(mCurrentButton == 1)
		{
			mManager.mSound[L"menu-select.wav"]->Play();
		}
		else if (mCurrentButton == 2)
		{
			PostMessage(MyWindow::GetInstance().GetWindowHandle(), WM_DESTROY, 0, 0);
		}
	}

	//mCamera.LookAtObject(mObject2);
	for (int i = 0; i < 3; i++)
		mButtons[i].Update(_deltaTime);
}

void MySceneLobby::Render()
{
	mBackground.Render();
	mTitle.Render();

	for (int i = 0; i < 3; i++)
		mButtons[i].Render();
}

void MySceneLobby::Release()
{
	mManager.mSound[L"theme.ogg"]->Stop();
}

void MySceneLobby::Reset()
{
}

void MySceneLobby::Start()
{
	mManager.mSound[L"theme.ogg"]->Stop();
	mManager.mSound[L"theme.ogg"]->Play(true);
	mManager.mSound[L"ashrams.ogg"]->Stop();
}

void MySceneLobby::End()
{
}
