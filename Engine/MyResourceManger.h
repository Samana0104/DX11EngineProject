#pragma once
#include "DefaultResource.h"
#include "MyTextureHandler.h"
#include "MyMeshHandler.h"
#include "MyFontHandler.h"

namespace MyProject
{
	class MyResourceManager : public Singleton<MyResourceManager>
	{
	public:
		MyTextureHandler mTextureHandler;
		MyMeshHandler	 mMeshHandler;
		MyFontHandler	 mFontHandler;
		
	private:
		void CreateDefaultFonts();
		void CreateDefaultMeshes();
		void CreateDefaultTextures();

	public:
		void CreateDafultResource();
	};
}

