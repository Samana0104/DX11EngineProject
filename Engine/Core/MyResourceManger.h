#pragma once
#include "DefaultResource.h"
#include "MyTextureHandler.h"
#include "MyMeshHandler.h"
#include "MyFontHandler.h"
#include "MyShaderHandler.h"
#include "MySoundHandler.h"

namespace MyProject
{
	class MyResourceManager : public Singleton<MyResourceManager>
	{
	public:
		MyTextureHandler mTexture;
		MyMeshHandler	 mMesh;
		MyFontHandler	 mFont;
		MyShaderHandler  mShader;
		MySoundHandler	 mSound;
		
	private:
		friend class Singleton<MyResourceManager>;
		MyResourceManager() = default;

		void CreateDefaultFonts();
		void CreateDefaultMeshes();
		void CreateDefaultTextures();
		void CreateDefaultShaders();
		void CreateDefaultSounds();

	public:
		void CreateDafultResource();
	};
}

