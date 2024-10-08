#pragma once
#include "CoreAPI.h"

namespace HBSoft
{
    class Object2D;

    enum class SpriteType : int
    {
        UV_RECT = 0,
        IMAGE   = 1,
    };

    class Sprite
    {
    private:
        std::vector<RECT_F>      m_spriteUVRects;
        std::vector<TEXTURE_KEY> m_spriteTextures;

        SpriteType  m_spriteType;
        TEXTURE_KEY m_spriteMainKey;
        SHADER_KEY  m_spriteShaderKey;

        int m_spriteCount;

    public:
        Sprite() = default;

        const RECT_F&      GetUVRect(size_t _idx);
        const TEXTURE_KEY& GetTextureKey(size_t _idx) const;
        const TEXTURE_KEY& GetTextureMainKey() const;
        const SpriteType&  GetSpriteType() const;

        bool LoadScript(wstringV _filePath);

        void Render(Object2D& obj, size_t idx);

        size_t GetSize() const;
    };
}  // namespace HBSoft
