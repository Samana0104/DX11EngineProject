#pragma once
#include "MyActor.h"
#include "CollisionComponent.h"

namespace MyProject
{
	class MyTile : public MyActor
	{
	private:
		RECT_F mUV	   = { };

		int	   mRow	   = 0;
		int	   mColumn = 0;

	private:
		virtual void OnCollision(RECT_F& _self, RECT_F& _target, MyActor& _targetObj) override;

	public:
		MyTile();

		void SetUVRect(const RECT_F _uv);
		void SetRow(const int _row);
		void SetColumn(const int _column);

		int GetRow() const;
		int GetColumn() const;

		const RECT_F& GetUVRect() const;


		virtual void Update(const float _deltaTime) override;
		virtual void Render();
	};
}

