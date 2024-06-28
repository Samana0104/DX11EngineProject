#include "pch.h"
#include "MyCore.h"
#include "MySceneManager.h"
using namespace MyProject;

class Sample : public MyCore 
{
private:
	MySceneManager mSceneManager;

public:
	Sample()
	{
		Init();
	}

	~Sample()
	{
		Release();
	}

	virtual void Init() override
	{
		mSceneManager.Init();
	}
	virtual void Update(const float _deltaTime) override
	{
		mSceneManager.Update(_deltaTime);
	}

	virtual void Render() override
	{
		mSceneManager.Render();
	}

	virtual void Release() override
	{
		mSceneManager.Release();
	}

};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR
	pCmdLine, int nCmdShow)
{
	MyCore::INITIAL_SETUP(hInstance, 1200, 800);
	Sample sample;

	sample.GameRun();
	return 0;
}