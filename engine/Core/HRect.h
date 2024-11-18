/*
author : ���Ѻ�
description : �Ѻ� ����Ʈ�� Rect ������ �����ϱ� ���� �ҽ� ����
�ϵ� D2D1�̴� Rect�̴� ��ĸ��߱� ¥������ ���Ŀ� �ڵ� ��ȯ�ǵ��� ����

version: 1.0.0
date: 2024-11-05
*/

#pragma once
#include <Windows.h>
#include "glm/glm.hpp"

namespace HBSoft
{
    struct HRect
    {
        float left;
        float top;
        float right;
        float bottom;

        template <class T1, class T2, class T3, class T4>
        HRect(const T1& a, const T2& b, const T3& c, const T4& d);

        HRect();

        HRect operator=(const HRect& ref);
        HRect operator+(const HRect& ref);
        HRect operator-(const HRect& ref);
        HRect operator*(const HRect& ref);

        operator D2D1_RECT_F();
        operator D2D1_RECT_L();
        operator D2D1_RECT_U();
        operator const D2D1_RECT_F();
        operator const D2D1_RECT_L();
        operator const D2D1_RECT_U();
    };

    inline HRect::HRect()
        : left(0.f), top(0.f), right(0.f), bottom(0.f)
    {}

    template <class T1, class T2, class T3, class T4>
    inline HRect::HRect(const T1& a, const T2& b, const T3& c, const T4& d)
    {
        left   = static_cast<float>(a);
        top    = static_cast<float>(b);
        right  = static_cast<float>(c);
        bottom = static_cast<float>(d);
    }

    inline HRect HRect::operator=(const HRect& ref)
    {
        left   = static_cast<float>(ref.left);
        top    = static_cast<float>(ref.top);
        right  = static_cast<float>(ref.right);
        bottom = static_cast<float>(ref.bottom);
        return *this;
    }

    inline HRect HRect::operator+(const HRect& ref)
    {
        return {static_cast<float>(left + ref.left),
                static_cast<float>(top + ref.top),
                static_cast<float>(right + ref.right),
                static_cast<float>(bottom + ref.bottom)};
    }

    inline HRect HRect::operator-(const HRect& ref)
    {
        return {static_cast<float>(left - ref.left),
                static_cast<float>(top - ref.top),
                static_cast<float>(right - ref.right),
                static_cast<float>(bottom - ref.bottom)};
    }

    inline HRect HRect::operator*(const HRect& ref)
    {
        return {static_cast<float>(left * ref.left),
                static_cast<float>(top * ref.top),
                static_cast<float>(right * ref.right),
                static_cast<float>(bottom * ref.bottom)};
    }

    inline HRect::operator D2D1_RECT_F()
    {
        return {static_cast<FLOAT>(left),
                static_cast<FLOAT>(top),
                static_cast<FLOAT>(right),
                static_cast<FLOAT>(bottom)};
    }

    inline HRect::operator D2D1_RECT_L()
    {
        return {static_cast<LONG>(left),
                static_cast<LONG>(top),
                static_cast<LONG>(right),
                static_cast<LONG>(bottom)};
    }

    inline HRect::operator D2D1_RECT_U()
    {
        return {static_cast<UINT32>(left),
                static_cast<UINT32>(top),
                static_cast<UINT32>(right),
                static_cast<UINT32>(bottom)};
    }

    inline HRect::operator const D2D1_RECT_F()
    {
        return static_cast<D2D1_RECT_F>(*this);
    }

    inline HRect::operator const D2D1_RECT_L()
    {
        return static_cast<D2D1_RECT_L>(*this);
    }

    inline HRect::operator const D2D1_RECT_U()
    {
        return static_cast<D2D1_RECT_U>(*this);
    }
}  // namespace HBSoft
