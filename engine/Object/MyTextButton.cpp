#include "pch.h"
#include "MyTextButton.h"
using namespace MyProject;

MyTextButton::MyTextButton()
{
	mBtnLeftObj->SetScale({ 18.f, 13.f });
	mBtnLeftObj->AddScaleAsRatio(0.4f);
	mBtnRightObj->SetScale({ 18.f, 13.f });
	mBtnRightObj->AddScaleAsRatio(0.4f);

	mBtnLeftSprite.SetSpriteKey(L"menu_left.sprite");
	mBtnLeftSprite.SetChangeTime(0.05f);
	mBtnRightSprite.SetSpriteKey(L"menu_right.sprite");
	mBtnRightSprite.SetChangeTime(0.05f);

	mTextRect = { 0.f, 0.f, 0.f, 0.f };
}

void MyTextButton::SetText(wstringV _text)
{
	mText = _text;
	SetScale();
}

void MyTextButton::SetScale()
{
	vec2 fontSize = mManager.mFont[L"BUTTON_FONT"]->GetTextSize(mText);
	float width = fontSize.x;

	vec2 mainLocation = mTransform.GetLocation();

	width *= MyTransformer2D::GetCartesianSize().x / D3Device::GetInstance().GetViewportSize().x;

	mBtnLeftObj->SetLocation({mainLocation.x-width/2.f -8.f, mainLocation.y-0.5f});
	mBtnRightObj->SetLocation({mainLocation.x+width/2.f + 8.f, mainLocation.y-0.5f});
	
	mainLocation = MyTransformer2D::CartesianToPixel(mainLocation);

	mTextRect =
	{
		mainLocation.x - fontSize.x * 0.5f,
		mainLocation.y - fontSize.y * 0.5f,
		mainLocation.x + fontSize.x * 0.5f,
		mainLocation.y + fontSize.y * 0.5f
	};
}

void MyTextButton::Update(const float _deltaTime)
{
	SetScale();
	mBtnLeftSprite.Update(_deltaTime);
	mBtnRightSprite.Update(_deltaTime);
}

void MyTextButton::Render()
{
	if (GetCurrentState() == SelectState::ACTIVE)
	{
		mBtnLeftSprite.Render(mBtnLeftObj);
		mManager.mMesh[mBtnLeftObj.GetMeshKey()]->Draw(mBtnLeftObj->GetModelMat());
		mBtnRightSprite.Render(mBtnRightObj);
		mManager.mMesh[mBtnRightObj.GetMeshKey()]->Draw(mBtnRightObj->GetModelMat());
	}
	mManager.mFont[L"BUTTON_FONT"]->DrawTexts(mText, mTextRect, { 1.f, 1.f, 1.f, 1.f });
}
