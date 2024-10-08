#include "pch.h"
#include "TileManager.h"
using namespace HBSoft;

TileManager::TileManager()
    : m_background(std::make_shared<Tile>())
{}

bool TileManager::LoadScript(const wstringV _filePath)
{
    FILE* fp_src = nullptr;

    _wfopen_s(&fp_src, _filePath.data(), _T("rt"));

    if (fp_src == nullptr)
        return false;

    //---------------------------

    TCHAR    buffer[256]  = {0};
    TCHAR    buffer1[256] = {0};
    TCHAR    buffer2[256] = {0};
    WCHAR    tileKey[2]   = {0};
    wstringV converter;
    int      readFrame = 0;
    int      isCollision;
    RECT_F   mUV;

    _fgetts(buffer, _countof(buffer), fp_src);  // #Background
    _fgetts(buffer, _countof(buffer), fp_src);  // #Background
    _stscanf_s(buffer,
               L"%f %f %f %f %s %s",
               &mUV.left,
               &mUV.top,
               &mUV.right,
               &mUV.bottom,
               buffer1,
               (unsigned int)_countof(buffer1),
               buffer2,
               (unsigned int)_countof(buffer2));

    m_background->SetUVRect(mUV);
    m_background->SetTextureKey(buffer1);
    m_background->SetShaderKey(buffer2);

    //----------------------------------------------------------

    _fgetts(buffer, _countof(buffer), fp_src);  // #BLOCK
                                                // ---------------------------
    _fgetts(buffer, _countof(buffer), fp_src);
    _stscanf_s(buffer, L"%d", &readFrame);

    for (int iFrame = 0; iFrame < readFrame; iFrame++)
    {
        auto tile = std::make_shared<Tile>();

        _fgetts(buffer, _countof(buffer), fp_src);
        _stscanf_s(buffer,
                   L"%s %d%f%f%f%f %s%s",
                   tileKey,
                   (unsigned int)_countof(tileKey),
                   &isCollision,
                   &mUV.left,
                   &mUV.top,
                   &mUV.right,
                   &mUV.bottom,
                   buffer1,
                   (unsigned int)_countof(buffer1),
                   buffer2,
                   (unsigned int)_countof(buffer2));

        tile->SetUVRect(mUV);
        tile->SetTextureKey(buffer1);
        tile->SetShaderKey(buffer2);
        tile->GetCollisionComponent().SetCollisionable(static_cast<bool>(isCollision));

        m_tiles.insert(std::make_pair(tileKey[0], tile));
    }

    //-----------------------------------------------------
    _fgetts(buffer, _countof(buffer), fp_src);  // #BLOCK

    while (true)
    {
        _fgetts(buffer, _countof(buffer), fp_src);
        _stscanf_s(buffer, L"%s", buffer1, (unsigned int)_countof(buffer1));

        converter = buffer1;

        if (converter.compare(L"#end") == 0)
            break;

        for (int i = 0; i < converter.size(); i++)
        {
            if (m_tiles.contains(converter[i]))
            {
                auto tile = std::make_shared<Tile>();
                {
                    tile->SetTextureKey(m_tiles[converter[i]]->GetTextureKey());
                    tile->SetUVRect(m_tiles[converter[i]]->GetUVRect());
                    tile->SetShaderKey(m_tiles[converter[i]]->GetShaderKey());
                    tile->GetCollisionComponent().SetCollisionable(
                    m_tiles[converter[i]]->GetCollisionComponent().IsCollisionable());
                    tile->SetRow(i);
                    tile->SetColumn(m_columns);
                }

                if (tile->GetCollisionComponent().IsCollisionable())
                    m_collisions.push_back(tile);
                m_tileMap.emplace_back(std::move(tile));
            }
        }
        m_columns++;
        m_rows = static_cast<int>(converter.size());
    }

    fclose(fp_src);

    m_isScriptLoaded = true;

    SetSize({162.f, 92.f});
    SetPosition({0.f, 0.f});
    return true;
}

void TileManager::SetPosition(const vec2 pos)
{
    if (!m_isScriptLoaded)
    {
        MessageBoxA(NULL, "Script Is Not Loaded", "[TileManager error]", MB_OK);
        return;
    }

    for (auto& tile : m_tileMap)
    {
        (*tile)->SetLocation(
        {pos.x + tile->GetRow() * m_tileSize.x - m_size.x * 0.5f + m_tileSize.x * 0.5f,
         pos.y + -tile->GetColumn() * m_tileSize.y + m_size.y * 0.5f - m_tileSize.y * 0.5f});
    }

    m_position = pos;
}

void TileManager::SetSize(const vec2 _size)
{
    if (!m_isScriptLoaded)
    {
        MessageBoxA(NULL, "Script Is Not Loaded", "[TileManager error]", MB_OK);
        return;
    }

    float widthPerTile  = _size.x / static_cast<float>(m_rows);
    float heightPerTile = _size.y / static_cast<float>(m_columns);

    for (auto& tile : m_tileMap)
    {
        (*tile)->SetScale({widthPerTile, heightPerTile});
        tile->GetCollisionComponent().ResizeCollisionArea();
    }

    (*m_background)->SetScale({widthPerTile * 2.5f, heightPerTile * 2.5f});
    m_size     = _size;
    m_tileSize = {widthPerTile, heightPerTile};
}

const vec2& TileManager::GetTileSize() const
{
    return m_tileSize;
}

void TileManager::ProcessCollision(Actor& _actor)
{
    for (auto& tile : m_collisions)
        tile->GetCollisionComponent().IsCollisionWithEvent(_actor.GetCollisionComponent());
}

void TileManager::Render()
{
    // background size = 2 * tile size
    for (float i = 0; i < m_columns + 0.5f; i += 2.5f)
    {
        for (float j = 0; j < m_rows + 0.5f; j += 2.5f)
        {
            (*m_background)
            ->SetLocation({j * m_tileSize.x - m_size.x * 0.5f, -i * m_tileSize.y + m_size.y * 0.5f});

            m_background->Render();
        }
    }

    for (auto& tile : m_tileMap)
        tile->Render();
}
