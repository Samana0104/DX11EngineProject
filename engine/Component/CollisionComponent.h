#pragma once
#include "Transform2D.h"
#include "Mesh2D.h"

namespace HBSoft
{
    // ���߿� ���� �浹 ������ ���� �޽� ����� ����
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
        // ���߿� ���� ��� �浹 ����������?

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
        // �浹 ó�� �� �� �˾Ƽ� ���� �� ��� �� ��ȯ rt1 �ڽ� rt2 Ÿ��

        static bool IsPointInRect(const RECT_F rt1, const vec2 pt);
        static bool IsAABBCollision(const RECT_F& rt1, const RECT_F& rt2);

        // �� �ΰ��� �� ������
        static bool IsAABBCollision(const Transform2D& objM, const Transform2D& targetM);
        static bool IsOBBCollision(const Transform2D& objM, const Transform2D& targetM);
    };
}  // namespace HBSoft
