/*
author : 변한빛
description : 2D 오브젝트의 이동, 회전, 스케일을 조정하기 위해 만들어진 클래스

version: 1.0.0
date: 2024-10-08
*/

#pragma once
#include "CoreAPI.h"

namespace HBSoft
{
    class Transform2D
    {
    private:
        inline static vec2 mCartesianSize = {160.f, 90.f};

        vec2  m_location;
        vec2  m_scale;
        float m_angle;
        mat3  m_trsMat;

    private:
        void CalculateScaleRotationMat();

    public:
        Transform2D();

        void         InitTransform();
        Transform2D& AddLocation(const vec2 pos);
        Transform2D& AddRotation(const float angle);
        Transform2D& AddScale(const vec2 scale);
        Transform2D& AddScaleAsRatio(const float ratio);
        Transform2D& SetLocation(const vec2 pos);
        Transform2D& SetRotation(const float angle);
        Transform2D& SetScale(const vec2 scale);

        void MultiplyToTRSMat(const mat3& mat);

        // 벡터로 계산하고 맵핑된 벡터 반환
        vec2 CalculateTRSAsVec(const vec2 pos);

        const mat3& GetModelMat() const;
        const mat3  GetViewMat() const;
        const mat3  GetTransposMat() const;
        const mat3  GetScaleMat() const;
        const mat3  GetRotationMat() const;

        const vec2& GetLocation() const;
        const vec2& GetScale() const;
        float       GetAngle() const;

        // 위치 기준 플레이어 rect
        RECT_F GetCartesianRectF() const;
        RECT_F GetCartesianScaleRectF() const;
        RECT_F GetPixelRectF() const;

        Transform2D* operator->();
        Transform2D& operator=(const Transform2D& ref);

        static void SetCartesianSize(const vec2 pos);
        static vec2 GetCartesianSize();

        static RECT_F CartesianToPixelRect(const RECT_F rect);
        static vec2   CartesianToNDC(const vec2 pos);
        static vec2   CartesianToPixel(const vec2 pos);
        static vec2   CartesianToPolar(const vec2 pos);
        static vec2   PolarToCartesian(const vec2 pos);
        static vec2   PixelToCartesian(const vec2 pos);
        static vec2   PixelToNDC(const vec2 pos, const vec2 rectSize);

        static vec2 RotateAsAngle(const vec2 pos, const float angle);
        static vec2 RotateAsRadian(const vec2 pos, const float radian);
        static vec2 ResizeScale(const vec2 pos, const vec2 scale);

        template <typename T>
        static T    lerp(const T a, const T b, float t);
        static vec2 Slerp(const vec2 pos1, const vec2 pos2, float t);
    };

    template <typename T>
    inline T Transform2D::lerp(const T a, const T b, float t)
    {
        t = glm::clamp(t, 0.f, 1.f);
        return b * t + a * (1 - t);
    }
}  // namespace HBSoft
