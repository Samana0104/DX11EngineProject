#pragma once
#include "MyTransformer2D.h"
#include "MyMesh2D.h"

namespace MyProject
{
	// 나중에 다중 충돌 구현을 위해 메쉬 헤더만 포함
	enum CollisionType
	{
		CLICK=0,
		RECT
	};
	
	class MyActor;

	using COLLISION_FUNC = std::function<void(RECT_F&, RECT_F&, MyActor&)>;

	class CollisionComponent
	{
	private:
		bool mIsCollisionable = true;

		MyActor& mObj;

		std::vector<RECT_F>	 mCollisionAreas;
		COLLISION_FUNC		 mCollisionFunc;

	public:
		CollisionComponent(MyActor& _obj);

		void AddCollisionArea(const RECT_F _collsionArea);
		void AddCollisionArea(const vec2 _scaleVec);
		// 나중에 여러 모양 충돌 구현할지도?

		void SetCollisionable(bool _isCollisionable);
		void ClearCollisionAreas();

		bool IsCollision(const RECT_F& _target);
		void IsCollisionWithEvent(CollisionComponent& _targetCollision);

		bool IsCollisionable() const;
		
		void RegisterCollisionEvent(COLLISION_FUNC _func);
		void ResizeCollisionArea();

		vec2 GetCorrectionForCollision(const vec2 _offsetDir, const vec2 _targetLocation, 
			const RECT_F& _rt1, const RECT_F& _rt2);

		static RECT_F GetIntersectionRect(const RECT_F& _rt1, const RECT_F& _rt2);
		// 충돌 처리 날 시 알아서 보정 값 계산 후 반환 rt1 자신 rt2 타겟

		static bool IsPointInRect(const RECT_F rt1, const vec2 pt);
		static bool IsAABBCollision(const RECT_F& rt1, const RECT_F& rt2);

		// 이 두개는 손 봐야함
		static bool IsAABBCollision(const MyTransformer2D& _objM, const MyTransformer2D& _targetM);
		static bool IsOBBCollision(const MyTransformer2D& _objM, const MyTransformer2D& _targetM);
	};
}

