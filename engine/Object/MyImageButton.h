#pragma once
#include "MyButton.h"
#include "MyCamera.h"
#include "SpriteComponent.h"

namespace MyProject
{
	class MyImageButton : public MyButton
	{
	private:
		MyCamera*		mCamera = nullptr;
		MyObject		mRenderSprite;
		SpriteComponent mPointer;
		wstringV		mText;

	public:
		MyObject mImage;

	public:
		MyImageButton();
		
		void SetText(wstringV _text);
		void SetImage(TEXTURE_KEY _imageKey);
		void SetScale();

		virtual void Update(const float _deltaTime) override;
		virtual void Render() override;
	};
}

