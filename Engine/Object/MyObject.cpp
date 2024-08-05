#include "pch.h"
#include "MyObject.h"
using namespace MyProject;

void MyObject::SetImageScale()
{
	vec2 windowSize = MyWindow::GetInstance().GetWindowSizeVec2();
	vec2 imageSize = mManager.mTexture[mTextureKey]->GetTextureSizeVec2();
	vec2 cartesianSize = mTransform.GetCartesianSize();
	
	mTransform.SetScale((imageSize/windowSize) * cartesianSize);
}

void MyObject::SetColor(const vec4 _color)
{
	mColor = _color;
}

void MyObject::SetTextureKey(const TEXTURE_KEY _key)
{
	mTextureKey = _key;
}

void MyObject::SetMeshKey(const MESH_KEY _key)
{
	mMeshKey = _key;
}

void MyObject::SetShaderKey(const SHADER_KEY _key)
{
	mShaderKey = _key;
}

void MyObject::SetObjectID(const OBJECT_ID _objID)
{
	mObjectID = _objID;
}

void MyObject::SetObjectCode(const ObjectCode _objCode)
{
	mObjectCode = _objCode;
}


const vec4& MyObject::GetColor() const
{
	return mColor;
}

const MESH_KEY& MyObject::GetMeshKey() const
{
	return mMeshKey;
}

const TEXTURE_KEY& MyObject::GetTextureKey() const
{
	return mTextureKey;
}

const SHADER_KEY& MyObject::GetShaderKey() const
{
	return mShaderKey;
}

const ObjectCode& MyObject::GetObjectCode() const
{
	return mObjectCode;
}

const OBJECT_ID& MyObject::GetObjectID() const
{
	return mObjectID;
}

MyTransformer2D& MyObject::GetTransform() 
{
	return mTransform;
}

MyTransformer2D* MyObject::operator->()
{
	return &mTransform;
}

void MyObject::Update(const float _deltaTime)
{
}

void MyObject::Render()
{
	mManager.mShader[mShaderKey]->SetUpConfiguration();
	mManager.mTexture[mTextureKey]->Render();
	mManager.mMesh[mMeshKey]->Draw(mTransform.GetModelMat(), mColor);
}
