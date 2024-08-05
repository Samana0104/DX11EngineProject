#pragma once
#include "MyCoreAPI.h"
#include "MyTile.h"

namespace MyProject
{
	class MyTileManager
	{
	private:
		std::map<WCHAR, std::shared_ptr<MyTile>> mTiles;
		std::vector<std::shared_ptr<MyTile>>	 mTileMap;
		std::vector<std::shared_ptr<MyTile>>	 mCollisions;
		
		std::shared_ptr<MyTile>	mBackground;

		int		mRows    = 0;
		int		mColumns = 0;

		vec2	mPosition	= { 0.f, 0.f };
		vec2	mSize		= { 100.f, 100.f };
		vec2	mTileSize	= { 0.f, 0.f };

		bool    mIsScriptLoaded = false;

	public:
		MyTileManager();

		bool LoadScript(const wstringV _filePath);

		void SetPosition(const vec2 _pos);
		void SetSize(const vec2 _size);

		const vec2& GetTileSize() const;

		void ProcessCollision(MyActor & _actor);
		void Render();
	};
}

