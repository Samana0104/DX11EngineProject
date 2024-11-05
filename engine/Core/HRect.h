/*
author : 변한빛
description : 한빛 소프트의 Rect 단위를 정의하기 위한 소스 파일
하도 D2D1이니 Rect이니 양식맞추기 짜증나서 서식에 자동 변환되도록 만듬

version: 1.0.0
date: 2024-11-05
*/

#pragma once
#include <Windows.h>
#include <d2d1.h>

namespace HBSoft
{
    struct HRect
    {
        float left;
        float top;
        float right;
        float bottom;

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
