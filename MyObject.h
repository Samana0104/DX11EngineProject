#pragma once
#include "Component.h"

namespace MyProject
{
	class MyObject : public Component
	{
	private:
		std::string mTextureKey;
		std::string mMeshKey;
	};
}
