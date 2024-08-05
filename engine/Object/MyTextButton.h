#pragma once
#include "MyButton.h"
#include "SpriteComponent.h"

namespace MyProject
{
	class MyTextButton : public MyButton
	{
	private:
		MyObject mBtnLeftObj;
		MyObject mBtnRightObj;
		SpriteComponent mBtnLeftSprite;
		SpriteComponent mBtnRightSprite;
		wstringV mText;
		RECT_F	 mTextRect;

	public:
		MyTextButton();
		
		void SetText(wstringV _text);
		void SetScale();
		virtual void Update(const float _deltaTime) override;
		virtual void Render() override;
	};
}

