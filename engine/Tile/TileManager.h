#pragma once
#include "CoreAPI.h"
#include "Tile.h"

namespace HBSoft
{
    class TileManager
    {
    private:
        std::map<WCHAR, std::shared_ptr<Tile>> m_tiles;
        std::vector<std::shared_ptr<Tile>>     m_tileMap;
        std::vector<std::shared_ptr<Tile>>     m_collisions;

        std::shared_ptr<Tile> m_background;

        int m_rows    = 0;
        int m_columns = 0;

        vec2 m_position = {0.f, 0.f};
        vec2 m_size     = {100.f, 100.f};
        vec2 m_tileSize = {0.f, 0.f};

        bool m_isScriptLoaded = false;

    public:
        TileManager();

        bool LoadScript(const wstringV _filePath);

        void SetPosition(const vec2 _pos);
        void SetSize(const vec2 _size);

        const vec2& GetTileSize() const;

        void ProcessCollision(Actor& _actor);
        void Render();
    };
}  // namespace HBSoft
