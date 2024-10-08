#pragma once
#include "Mesh2D.h"

namespace HBSoft
{
    class Circle2D : public Mesh2D
    {
    private:
        size_t m_triangles;

    private:
        void CreateCircle2DVertex();

    public:
        Circle2D(const size_t triangles = 50);

        virtual void SetUVVertexAsRect(const RECT_F& rect, const vec2& imageSize) override;
    };
}  // namespace HBSoft
