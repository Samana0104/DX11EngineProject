#pragma once
#include "CoreAPI.h"

namespace HBSoft
{
    class Transform2D
    {
    private:
        static inline vec2 mCartesianSize = {160.f, 90.f};

        vec2  m_Location;
        vec2  m_Scale;
        float mAngle;
        mat3  mTRSMat;

    private:
        void CalculateScaleRotationMat();

    public:
        Transform2D();

        void         InitTransform();
        Transform2D& AddLocation(const vec2 _pos);
        Transform2D& AddRotation(const float _angle);
        Transform2D& AddScale(const vec2 _scale);
        Transform2D& AddScaleAsRatio(const float _ratio);
        Transform2D& SetLocation(const vec2 _pos);
        Transform2D& SetRotation(const float _angle);
        Transform2D& SetScale(const vec2 _scale);

        void MultiplyToTRSMat(const mat3& _mat);

        // 벡터로 계산하고 맵핑된 벡터 반환
        vec2 CalculateTRSAsVec(const vec2 _pos);

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

        Transform2D * operator->();
        Transform2D&  operator=(const Transform2D& _ref);

        static void SetCartesianSize(const vec2 _pos);
        static vec2 GetCartesianSize();

        static RECT_F CartesianToPixelRect(const RECT_F _rect);
        static vec2   CartesianToNDC(const vec2 _pos);
        static vec2   CartesianToPixel(const vec2 _pos);
        static vec2   CartesianToPolar(const vec2 _pos);
        static vec2   PolarToCartesian(const vec2 _pos);
        static vec2   PixelToCartesian(const vec2 _pos);
        static vec2   PixelToNDC(const vec2 _pos, const vec2 _rectSize);

        static vec2 RotateAsAngle(const vec2 _pos, const float _angle);
        static vec2 RotateAsRadian(const vec2 _pos, const float _radian);
        static vec2 ResizeScale(const vec2 _pos, const vec2 _scale);

        template <typename T>
        static T    lerp(const T a, const T b, float t);
        static vec2 Slerp(const vec2 _pos1, const vec2 _pos2, float t);
    };

    template <typename T>
    inline T Transform2D::lerp(const T a, const T b, float t)
    {
        t = glm::clamp(t, 0.f, 1.f);
        return b * t + a * (1 - t);
    }
}  // namespace HBSoft
