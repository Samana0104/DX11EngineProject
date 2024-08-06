#pragma once
#include "DefaultResource.h"
#include "MyTextureHandler.h"
#include "MyMeshHandler.h"
#include "MyFontHandler.h"
#include "MyShaderHandler.h"
#include "MySoundHandler.h"
#include "MySpriteHandler.h"

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
		MySpriteHandler  mSprite;
		
	private:
		friend class Singleton<MyResourceManager>;
		MyResourceManager() = default;

		void CreateDefaultFonts();
		void CreateDefaultMeshes();
		void CreateDefaultTextures();
		void CreateDefaultShaders();
		void CreateDefaultSounds();
		void CreateDefaultSprites();

	public:
		void CreateDafultResource();
	};
}

