#pragma once
#include "DefaultResource.h"
#include "MyTextureHandler.h"
#include "MyMeshHandler.h"
#include "MyFontHandler.h"
#include "MyShaderHandler.h"

namespace MyProject
{
	class MyResourceManager : public Singleton<MyResourceManager>
	{
	public:
		MyTextureHandler mTextureHandler;
		MyMeshHandler	 mMeshHandler;
		MyFontHandler	 mFontHandler;
		MyShaderHandler  mShaderHandler;
		
	private:
		friend class Singleton<MyResourceManager>;
		MyResourceManager() = default;

		void CreateDefaultFonts();
		void CreateDefaultMeshes();
		void CreateDefaultTextures();
		void CreateDefaultShaders();

	public:
		void CreateDafultResource();
	};
}

