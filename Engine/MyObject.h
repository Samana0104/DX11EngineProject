#pragma once
#include "Component.h"
#include "MyTransformer2D.h"

namespace MyProject
{
	class MyObject : public Component
	{
	private:
		MyTransformer2D		mTransform;

		TEXTURE_KEY	mTextureKey;
		MESH_KEY	mMeshKey;

	public:
		MyObject(TEXTURE_KEY _textureKey, MESH_KEY _meshKey)
		{
		}

		virtual void UpdateComponent();
		virtual void RenderComponent();
	};
}
