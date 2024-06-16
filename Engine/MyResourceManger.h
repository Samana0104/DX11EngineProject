#pragma once
#include "MyTextureHandler.h"
#include "MyMeshHandler.h"
#include "MyFontHandler.h"

namespace MyProject
{
	class MyResourceManager : public Singleton<MyResourceManager>
	{
	private:
		MyTextureHandler mTextureHandler;
		MyMeshHandler	 mMeshHandler;
		MyFontHandler	 mFontHandler;
		
		std::vector<std::string> mDefaultFont;
		std::vector<std::string> mDefaultMesh;
		std::vector<std::string> mDefaultTexture;

	public:
		
	};
}

