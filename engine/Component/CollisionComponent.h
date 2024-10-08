#pragma once
#include "Transform2D.h"
#include "Mesh2D.h"

namespace HBSoft
{
    // 나중에 다중 충돌 구현을 위해 메쉬 헤더만 포함
    enum CollisionType
    {
        CLICK = 0,
        RECT
    };

    class Actor;

    using COLLISION_FUNC = std::function<void(RECT_F&, RECT_F&, Actor&)>;

    class CollisionComponent
    {
    private:
        bool m_isCollisionable = true;

        Actor& m_obj;

        std::vector<RECT_F> m_collisionAreas;
        COLLISION_FUNC      m_collisionFunc;

    public:
        CollisionComponent(Actor& _obj);

        void AddCollisionArea(const RECT_F collsionArea);
        void AddCollisionArea(const vec2 scaleVec);
        // 나중에 여러 모양 충돌 구현할지도?

        void SetCollisionable(bool isCollisionable);
        void ClearCollisionAreas();

        bool IsCollision(const RECT_F& target);
        void IsCollisionWithEvent(CollisionComponent& targetCollision);

        bool IsCollisionable() const;

        void RegisterCollisionEvent(COLLISION_FUNC func);
        void ResizeCollisionArea();

        vec2 GetCorrectionForCollision(const vec2 offsetDir, const vec2 targetLocation,
                                       const RECT_F& rt1, const RECT_F& rt2);

        static RECT_F GetIntersectionRect(const RECT_F& rt1, const RECT_F& rt2);
        // 충돌 처리 날 시 알아서 보정 값 계산 후 반환 rt1 자신 rt2 타겟

        static bool IsPointInRect(const RECT_F rt1, const vec2 pt);
        static bool IsAABBCollision(const RECT_F& rt1, const RECT_F& rt2);

        // 이 두개는 손 봐야함
        static bool IsAABBCollision(const Transform2D& objM, const Transform2D& targetM);
        static bool IsOBBCollision(const Transform2D& objM, const Transform2D& targetM);
    };
}  // namespace HBSoft
