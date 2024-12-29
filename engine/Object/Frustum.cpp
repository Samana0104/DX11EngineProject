#include "pch.h"
#include "Frustum.h"
using namespace HBSoft;

void Frustum::Set(const mat4& viewMat, const mat4& projMat)
{
    mat4 matVP     = projMat * viewMat;
    mat4 inverseVP = glm::inverse(matVP);
    // 상단
    // 5    6
    // 1    2
    // 하단
    // 4    7
    // 0    3

    m_frustum[0] = vec3(-1.0f, -1.0f, 0.0f);
    m_frustum[1] = vec3(-1.0f, 1.0f, 0.0f);
    m_frustum[2] = vec3(1.0f, 1.0f, 0.0f);
    m_frustum[3] = vec3(1.0f, -1.0f, 0.0f);
    m_frustum[4] = vec3(-1.0f, -1.0f, 1.0f);
    m_frustum[5] = vec3(-1.0f, 1.0f, 1.0f);
    m_frustum[6] = vec3(1.0f, 1.0f, 1.0f);
    m_frustum[7] = vec3(1.0f, -1.0f, 1.0f);

    for (int i = 0; i < 8; i++)
    {
        vec4 vpCoord     = vec4(m_frustum[i], 1.f);
        vec4 worldCoord  = inverseVP * vpCoord;
        worldCoord      /= worldCoord.w;

        m_frustum[i] = worldCoord;
    }

    m_plane[0].Set(m_frustum[5], m_frustum[0], m_frustum[1]);  // 좌 평면(left)
    m_plane[1].Set(m_frustum[3], m_frustum[6], m_frustum[2]);  // 우 평면(right)
    m_plane[2].Set(m_frustum[5], m_frustum[2], m_frustum[6]);  // 상 평면(top)
    m_plane[3].Set(m_frustum[0], m_frustum[7], m_frustum[3]);  // 하 평면(bottom)
    m_plane[4].Set(m_frustum[0], m_frustum[2], m_frustum[1]);  // 근 평면(near)
    m_plane[5].Set(m_frustum[6], m_frustum[4], m_frustum[5]);  // 원 평면(far)
}

bool Frustum::IsFrustumInBox(const Box& box)
{
    vec3 axisX = box.obb.axis[0] * box.obb.distance[0];
    vec3 axisY = box.obb.axis[1] * box.obb.distance[1];
    vec3 axisZ = box.obb.axis[2] * box.obb.distance[2];

    float fDistance = 0.0f;

    for (int p = 0; p < 6; p++)
    {
        float fPlaneToCenter = m_plane[p].a * box.obb.center.x + m_plane[p].b * box.obb.center.y +
                               m_plane[p].c * box.obb.center.z + m_plane[p].d;

        fDistance  = fabs(m_plane[p].a * axisX.x + m_plane[p].b * axisX.y + m_plane[p].c * axisX.z);
        fDistance += fabs(m_plane[p].a * axisY.x + m_plane[p].b * axisY.y + m_plane[p].c * axisY.z);
        fDistance += fabs(m_plane[p].a * axisZ.x + m_plane[p].b * axisZ.y + m_plane[p].c * axisZ.z);
        if (fPlaneToCenter * 0.3f < -fDistance)
            return false;
    }
    return true;
}
