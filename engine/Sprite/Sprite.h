#pragma once
#include "CoreAPI.h"

namespace HBSoft
{
    class Object;

    enum class SpriteType : int
    {
        UV_RECT = 0,
        IMAGE   = 1,
    };

    class Sprite
    {
    private:
        std::vector<RECT_F>      mSpriteUVRects;
        std::vector<TEXTURE_KEY> mSpriteTextures;

        SpriteType  mSpriteType;
        TEXTURE_KEY mSpriteMainKey;
        SHADER_KEY  mSpriteShaderKey;

        int mSpriteCount;

    public:
        Sprite() = default;

        const RECT_F&      GetUVRect(size_t _idx);
        const TEXTURE_KEY& GetTextureKey(size_t _idx) const;
        const TEXTURE_KEY& GetTextureMainKey() const;
        const SpriteType&  GetSpriteType() const;

        bool LoadScript(wstringV _filePath);

        void Render(Object& _obj, size_t idx);

        size_t GetSize() const;
    };
}  // namespace HBSoft
