#pragma once
#include "MyTimer.h"
#include "MyInput.h"
#include "MyWindow.h"
#include "MyShader.h"
#include "Box2D.h"
#include "MyFontHandler.h"

namespace MyProject
{
	class MyCore : public Component
	{
	private:
		MyShader		mShader;
		D3D11_VIEWPORT	mViewPort;

	private:
		MyCore(const MyCore&) = delete;
		void operator=(const MyCore&) = delete;

		void	InitViewPort();
		void	GamePreFrame();
		void	GameFrame();
		void	GamePostFrame();
		void	GamePreRender();
		void	GameRender();
		void	GamePostRender();
		void	GameInit();
		void	GameRelease();

	protected:
		MyTimer	mTimer;
		MyInput	mInput;

		MyFontHandler	mFont;
	protected:
		MyCore() = default;

		virtual void InitComponent() = 0;
		virtual void UpdateComponent() override = 0;
		virtual void RenderComponent() override = 0;

	public:
		void GameRun();
		void DrawTextForDebuging() const;

		D3D11_VIEWPORT& GetViewPort();
	};
}
