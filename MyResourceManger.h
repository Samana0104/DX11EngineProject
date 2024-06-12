#pragma once
#include "MyTextureHandler.h"
#include "MyMeshHandler.h"
#include "MyFontHandler.h"

namespace MyProject
{
	class MyResourceManager : public Singleton<MyResourceManager>
	{
	private:
		std::unordered_map<std::string, MyTextureHandler>	mTextureHandler;
		std::unordered_map<std::string, MyMeshHandler>		mMeshHandler;
		std::unordered_map<std::string, MyFontHandler>		mFontHandler;

	public:
		
	};
}

