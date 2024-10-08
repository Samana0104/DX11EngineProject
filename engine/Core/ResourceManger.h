#pragma once
#include "DefaultResource.h"
#include "TextureHandler.h"
#include "MeshHandler.h"
#include "MyFontHandler.h"
#include "ShaderHandler.h"
#include "SoundHandler.h"
#include "SpriteHandler.h"

namespace HBSoft
{
    class MyResourceManager : public Singleton<MyResourceManager>
    {
    public:
        TextureHandler mTexture;
        MeshHandler    mMesh;
        MyFontHandler  mFont;
        ShaderHandler  mShader;
        SoundHandler   mSound;
        SpriteHandler  mSprite;

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
}  // namespace HBSoft
