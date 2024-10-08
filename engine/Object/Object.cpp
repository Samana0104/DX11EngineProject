#include "pch.h"
#include "Object.h"
using namespace HBSoft;

void Object::SetImageScale()
{
	vec2 windowSize = MyWindow::GetInstance().GetWindowSizeVec2();
	vec2 imageSize = mManager.mTexture[mTextureKey]->GetTextureSizeVec2();
	vec2 cartesianSize = mTransform.GetCartesianSize();
	
	mTransform.SetScale((imageSize/windowSize) * cartesianSize);
}

void Object::SetColor(const vec4 _color)
{
	mColor = _color;
}

void Object::SetTextureKey(const TEXTURE_KEY _key)
{
	mTextureKey = _key;
}

void Object::SetMeshKey(const MESH_KEY _key)
{
	mMeshKey = _key;
}

void Object::SetShaderKey(const SHADER_KEY _key)
{
	mShaderKey = _key;
}

void Object::SetObjectID(const OBJECT_ID _objID)
{
	mObjectID = _objID;
}

void Object::SetObjectCode(const ObjectCode _objCode)
{
	mObjectCode = _objCode;
}


const vec4& Object::GetColor() const
{
	return mColor;
}

const MESH_KEY& Object::GetMeshKey() const
{
	return mMeshKey;
}

const TEXTURE_KEY& Object::GetTextureKey() const
{
	return mTextureKey;
}

const SHADER_KEY& Object::GetShaderKey() const
{
	return mShaderKey;
}

const ObjectCode& Object::GetObjectCode() const
{
	return mObjectCode;
}

const OBJECT_ID& Object::GetObjectID() const
{
	return mObjectID;
}

Transform2D& Object::GetTransform() 
{
	return mTransform;
}

Transform2D* Object::operator->()
{
	return &mTransform;
}

void Object::Update(const float _deltaTime)
{
}

void Object::Render()
{
	mManager.mShader[mShaderKey]->SetUpConfiguration();
	mManager.mTexture[mTextureKey]->Render();
	mManager.mMesh[mMeshKey]->Draw(mTransform.GetModelMat(), mColor);
}
