#include "pch.h"
#include "MyActor.h"
using namespace MyProject;

void MyActor::SetColor(COLOR_F _color)
{
	mColor = _color;
}

COLOR_F MyActor::GetColor() const
{
	return mColor;
}

void MyActor::Update(const float _deltaTime)
{
}

void MyActor::Render(const mat3 _viewMat)
{
	vec4 color = { mColor.r, mColor.g, mColor.b, mColor.a };
	mManager.mTexture[mTextureKey]->RenderComponent();
	mManager.mMesh[mMeshKey]->Render(_viewMat * mTransform.GetModelMat(), color);
}
