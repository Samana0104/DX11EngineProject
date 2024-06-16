#pragma once
#include "Component.h"
#include "MyTransformer2D.h"

namespace MyProject
{
	class MyObject : public Component
	{
	private:
		MyTransformer2D		mTransform;
		UINT	mObjectID;

		std::string			mTextureKey;
		std::string			mMeshKey;

	public:
		MyObject(std::string _textureKey, std::string _meshKey)
		{
		}
		virtual void UpdateComponent();
		virtual void RenderComponent();
	};
}
