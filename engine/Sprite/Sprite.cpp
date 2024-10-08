#include "pch.h"
#include "Object2D.h"
#include "Sprite.h"
using namespace HBSoft;

const RECT_F& Sprite::GetUVRect(size_t _idx)
{
    return m_spriteUVRects[_idx];
}

const TEXTURE_KEY& Sprite::GetTextureKey(size_t _idx) const
{
    if (m_spriteType == SpriteType::UV_RECT)
        return m_spriteMainKey;
    else
        return m_spriteTextures[_idx];
}

const TEXTURE_KEY& Sprite::GetTextureMainKey() const
{
    return m_spriteMainKey;
}

const SpriteType& Sprite::GetSpriteType() const
{
    return m_spriteType;
}

bool Sprite::LoadScript(wstringV _filePath)
{
    FILE* fp_src = nullptr;

    TCHAR pBuffer[256]     = {0};
    TCHAR textureName[256] = {0};
    TCHAR shaderName[256]  = {0};

    int readFrame = 0;

    _wfopen_s(&fp_src, _filePath.data(), _T("rt"));

    if (fp_src == nullptr)
        return false;

    // ---------------------------
    _fgetts(pBuffer, _countof(pBuffer), fp_src);
    _stscanf_s(pBuffer,
               L"%d %d %s %s",
               &m_spriteCount,
               &m_spriteType,
               textureName,
               (unsigned int)_countof(textureName),
               shaderName,
               (unsigned int)_countof(shaderName));
    // ---------------------------

    m_spriteMainKey   = textureName;
    m_spriteShaderKey = shaderName;

    switch (m_spriteType)
    {
    case SpriteType::UV_RECT:
        m_spriteUVRects.reserve(m_spriteCount);
        RECT_F rt;

        for (int iFrame = 0; iFrame < m_spriteCount; iFrame++)
        {
            _fgetts(pBuffer, _countof(pBuffer), fp_src);
            _stscanf_s(pBuffer, L"%d %f %f %f %f", &readFrame, &rt.left, &rt.top, &rt.right, &rt.bottom);

            m_spriteUVRects.push_back(rt);
        }
        break;
    case SpriteType::IMAGE:
        m_spriteTextures.reserve(m_spriteCount);

        for (int iFrame = 0; iFrame < m_spriteCount; iFrame++)
        {
            _fgetts(pBuffer, _countof(pBuffer), fp_src);
            _stscanf_s(pBuffer,
                       _T("%d %s"),
                       &readFrame,
                       textureName,
                       (unsigned int)_countof(textureName));
            m_spriteTextures.push_back(textureName);
        }
        break;
    }
    fclose(fp_src);

    return true;
}

void Sprite::Render(Object2D& obj, size_t idx)
{
    ResourceManager& m_manager = ResourceManager::GetInstance();

    m_manager.m_shader[m_spriteShaderKey]->SetUpConfiguration();

    switch (m_spriteType)
    {
    case SpriteType::UV_RECT:
        vec2 imageSize = m_manager.m_texture[m_spriteMainKey]->GetTextureSizeVec2();
        m_manager.m_texture[m_spriteMainKey]->Render();
        m_manager.m_mesh[obj.GetMeshKey()]->SetUVVertexAsRect(m_spriteUVRects[idx], imageSize);
        break;

    case SpriteType::IMAGE:
        m_manager.m_texture[m_spriteTextures[idx]]->Render();
        break;
    }
}

size_t Sprite::GetSize() const
{
    return m_spriteCount;
}
