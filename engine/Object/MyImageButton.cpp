#include "pch.h"
#include "MyImageButton.h"
using namespace MyProject;

MyImageButton::MyImageButton()
{
	mPointer.SetSpriteKey(L"menu-pointer.sprite");
	mPointer.SetChangeTime(0.05f);
	mRenderSprite->SetScale({ 6.f, 13.f });
	mImage.SetImageScale();
	mImage->AddScaleAsRatio(0.13f);
	mImage->AddLocation({ -2.f, 2.f });
}

void MyImageButton::SetText(wstringV _text)
{
	mText = _text;
}

void MyImageButton::SetImage(TEXTURE_KEY _imageKey)
{
	mImage.SetTextureKey(_imageKey);
}

void MyImageButton::SetScale()
{
}

void MyImageButton::Update(const float _deltaTime)
{
	mPointer.Update(_deltaTime);
}

void MyImageButton::Render()
{
	vec2 viewportSize = D3Device::GetInstance().GetViewportSize();
	vec2 windowSize = MyWindow::GetInstance().GetWindowSizeVec2();
	float fontSize = mManager.mFont[L"BUTTON_FONT"]->GetFontSize();
	float length = mText.size() * fontSize;

	RECT_F rt =
	{
		windowSize.x*0.5f - length * 0.5f,
		windowSize.y*0.5f + viewportSize.y*0.43f - fontSize * 0.5f,
		windowSize.x*0.5f + length * 0.5f,
		windowSize.y*0.5f + viewportSize.y*0.43f + fontSize * 0.5f,
	};

	mManager.mShader[L"PixelShaderLight.hlsl"]->SetUpConfiguration();
	mManager.mTexture[mImage.GetTextureKey()]->Render();
	mManager.mMesh[mImage.GetMeshKey()]->Draw(mTransform.GetTransposMat() * mImage->GetModelMat());

	if (GetCurrentState() == SelectState::ACTIVE)
	{
		mPointer.Render(mRenderSprite);
		mManager.mMesh[mRenderSprite.GetMeshKey()]->Draw(mTransform.GetTransposMat() * mRenderSprite->GetModelMat());
		mManager.mFont[L"BUTTON_FONT"]->DrawTexts(mText, rt, { 1.f, 1.f, 1.f, 1.f });
	}
}
