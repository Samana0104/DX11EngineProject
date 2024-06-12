#pragma once
#include "Component.h"
#include "MyTransformer2D.h"

namespace MyProject
{
	class MyObject : public Component
	{
	private:
		MyTransformer2D		mTransform;
		std::string			mTextureKey;
		std::string			mMeshKey;
	};
}
