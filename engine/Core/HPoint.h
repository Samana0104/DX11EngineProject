/*
author : 변한빛
description : 한빛 소프트의 포인트 단위를 정의하기 위한 헤더 파일
하도 D2D1이니 Rect이니 양식맞추기 짜증나서 서식에 자동 변환되도록 만듬

version: 1.0.8
date: 2024-12-01
*/

#pragma once
#include "d2d1.h"
#include "glm/glm.hpp"

namespace HBSoft
{
    struct HPoint
    {
        float x;
        float y;

        template <class T1, class T2>
        HPoint(const T1& a, const T2& b);

        HPoint();

        HPoint operator=(const HPoint& ref);
        HPoint operator=(const D2D1_POINT_2F& ref);
        HPoint operator=(const D2D1_POINT_2L& ref);
        HPoint operator=(const D2D1_POINT_2U& ref);
        HPoint operator=(const glm::vec2& ref);

        HPoint operator+(const HPoint& ref);
        HPoint operator+(const D2D1_POINT_2F& ref);
        HPoint operator+(const D2D1_POINT_2L& ref);
        HPoint operator+(const D2D1_POINT_2U& ref);
        HPoint operator+(const glm::vec2& ref);

        HPoint operator-(const HPoint& ref);
        HPoint operator-(const D2D1_POINT_2F& ref);
        HPoint operator-(const D2D1_POINT_2L& ref);
        HPoint operator-(const D2D1_POINT_2U& ref);
        HPoint operator-(const glm::vec2& ref);

        HPoint operator*(const HPoint& ref);
        HPoint operator*(const D2D1_POINT_2F& ref);
        HPoint operator*(const D2D1_POINT_2L& ref);
        HPoint operator*(const D2D1_POINT_2U& ref);
        HPoint operator*(const glm::vec2& ref);

        template <class T>
        HPoint operator*(const T num);


        operator D2D1_POINT_2F() const;
        operator D2D1_POINT_2L() const;
        operator D2D1_POINT_2U() const;
        operator glm::vec2() const;

        operator const D2D1_POINT_2F() const;
        operator const D2D1_POINT_2L() const;
        operator const D2D1_POINT_2U() const;
        operator const glm::vec2() const;
    };

    inline HPoint::HPoint()
        : x(0.f), y(0.f)
    {}

    inline HPoint HPoint::operator=(const HPoint& ref)
    {
        x = static_cast<float>(ref.x);
        y = static_cast<float>(ref.y);
        return *this;
    }

    inline HPoint HPoint::operator=(const D2D1_POINT_2F& ref)
    {
        x = static_cast<float>(ref.x);
        y = static_cast<float>(ref.y);
        return *this;
    }

    inline HPoint HPoint::operator=(const D2D1_POINT_2L& ref)
    {
        x = static_cast<float>(ref.x);
        y = static_cast<float>(ref.y);
        return *this;
    }

    inline HPoint HPoint::operator=(const D2D1_POINT_2U& ref)
    {
        x = static_cast<float>(ref.x);
        y = static_cast<float>(ref.y);
        return *this;
    }

    inline HPoint HPoint::operator=(const glm::vec2& ref)
    {
        x = static_cast<float>(ref.x);
        y = static_cast<float>(ref.y);
        return *this;
    }

    inline HPoint HPoint::operator+(const HPoint& ref)
    {
        return {static_cast<float>(x + ref.x), static_cast<float>(y + ref.y)};
    }

    inline HPoint HPoint::operator+(const D2D1_POINT_2F& ref)
    {
        return {static_cast<float>(x + ref.x), static_cast<float>(y + ref.y)};
    }

    inline HPoint HPoint::operator+(const D2D1_POINT_2L& ref)
    {
        return {static_cast<float>(x + ref.x), static_cast<float>(y + ref.y)};
    }

    inline HPoint HPoint::operator+(const D2D1_POINT_2U& ref)
    {
        return {static_cast<float>(x + ref.x), static_cast<float>(y + ref.y)};
    }

    inline HPoint HPoint::operator+(const glm::vec2& ref)
    {
        return {static_cast<float>(x + ref.x), static_cast<float>(y + ref.y)};
    }

    inline HPoint HPoint::operator-(const HPoint& ref)
    {
        return {static_cast<float>(x - ref.x), static_cast<float>(y - ref.y)};
    }

    inline HPoint HPoint::operator-(const D2D1_POINT_2F& ref)
    {
        return {static_cast<float>(x - ref.x), static_cast<float>(y - ref.y)};
    }

    inline HPoint HPoint::operator-(const D2D1_POINT_2L& ref)
    {
        return {static_cast<float>(x - ref.x), static_cast<float>(y - ref.y)};
    }

    inline HPoint HPoint::operator-(const D2D1_POINT_2U& ref)
    {
        return {static_cast<float>(x - ref.x), static_cast<float>(y - ref.y)};
    }

    inline HPoint HPoint::operator-(const glm::vec2& ref)
    {
        return {static_cast<float>(x - ref.x), static_cast<float>(y - ref.y)};
    }

    inline HPoint HPoint::operator*(const HPoint& ref)
    {
        return {static_cast<float>(x * ref.x), static_cast<float>(y * ref.y)};
    }

    inline HPoint HPoint::operator*(const D2D1_POINT_2F& ref)
    {
        return {static_cast<float>(x * ref.x), static_cast<float>(y * ref.y)};
    }

    inline HPoint HPoint::operator*(const D2D1_POINT_2L& ref)
    {
        return {static_cast<float>(x * ref.x), static_cast<float>(y * ref.y)};
    }

    inline HPoint HPoint::operator*(const D2D1_POINT_2U& ref)
    {
        return {static_cast<float>(x * ref.x), static_cast<float>(y * ref.y)};
    }

    inline HPoint HPoint::operator*(const glm::vec2& ref)
    {
        return {static_cast<float>(x * ref.x), static_cast<float>(y * ref.y)};
    }

    inline HPoint::operator D2D1_POINT_2F() const
    {
        return {static_cast<FLOAT>(x), static_cast<FLOAT>(y)};
    }

    inline HPoint::operator D2D1_POINT_2L() const
    {
        return {static_cast<LONG>(x), static_cast<LONG>(y)};
    }

    inline HPoint::operator D2D1_POINT_2U() const
    {
        return {static_cast<UINT32>(x), static_cast<UINT32>(y)};
    }

    inline HPoint::operator glm::vec2() const
    {
        return glm::vec2(x, y);
    }

    inline HPoint::operator const D2D1_POINT_2F() const
    {
        return static_cast<D2D1_POINT_2F>(*this);
    }

    inline HPoint::operator const D2D1_POINT_2L() const
    {
        return static_cast<D2D1_POINT_2L>(*this);
    }

    inline HPoint::operator const D2D1_POINT_2U() const
    {
        return static_cast<D2D1_POINT_2U>(*this);
    }

    inline HPoint::operator const glm::vec2() const
    {
        return glm::vec2(x, y);
    }

    template <class T1, class T2>
    inline HPoint::HPoint(const T1& a, const T2& b)
    {
        x = static_cast<float>(a);
        y = static_cast<float>(b);
    }

    template <class T>
    inline HPoint HPoint::operator*(const T num)
    {
        return {static_cast<float>(num) * x, static_cast<float>(num) * y};
    }
}  // namespace HBSoft
