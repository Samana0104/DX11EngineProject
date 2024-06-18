#pragma once
#include "Component.h"
#include "D3Device.h"
#include "MyTransformer2D.h"
#include "MyResourceManger.h"

namespace MyProject
{
	class MyObject
	{
	private:
		MyTransformer2D		mTransform;

		TEXTURE_KEY	mTextureKey;
		MESH_KEY	mMeshKey;

		MyResourceManager& mManager = MyResourceManager::GetInstance();

	public:
		MyObject(TEXTURE_KEY _textureKey, MESH_KEY _meshKey);

		virtual void UpdateObject(float _deltaTime);
		virtual void RenderObject(const mat3 _viewMat);
	};
}
