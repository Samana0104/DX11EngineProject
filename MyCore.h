#pragma once
#include "MyTimer.h"
#include "MyWriterFont.h"
#include "MyInput.h"
#include "MyWindow.h"
#include "MyShader.h"
#include "Box2D.h"

namespace MyProject
{
	class MyCore : protected Component
	{
	private:
		std::map<std::string, std::shared_ptr<MyWriterFont>> mGameFonts;
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
		void	DebugRender();
		void	GameInit();
		void	GameRelease();

		virtual void InitComponent() override = 0;
		virtual void UpdateComponent() override = 0;
		virtual void RenderComponent() override = 0;
		virtual void ReleaseComponent() override = 0;

	protected:
		MyTimer	mTimer;
		MyInput	mInput;

	protected:
		MyCore() = default;

	public:
		void CreateTextComponent(const std::string key, std::wstring _fontName, FLOAT _fontSize, COLOR_F _color);
		void AddTextComponent(const std::string _key, std::shared_ptr<MyWriterFont> _fonts);
		void GameRun();
		void DrawTextForDebuging() const;

		MyWriterFont& GetTextComponent(const std::string _key);
		D3D11_VIEWPORT& GetViewPort();
	};
}
