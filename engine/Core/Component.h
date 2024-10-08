#pragma once
#include "pch.h"

namespace HBSoft
{
    using namespace Microsoft::WRL;
    using namespace glm;

    using COLOR_F = D2D1_COLOR_F;

    // Pixel coordinate
    using RECT_L  = D2D1_RECT_L;
    using RECT_F  = D2D1_RECT_F;
    using RECT_U  = D2D1_RECT_U;
    using POINT_L = D2D1_POINT_2L;
    using POINT_F = D2D1_POINT_2F;
    using POINT_U = D2D1_POINT_2U;

    using stringV  = std::string_view;
    using wstringV = std::wstring_view;
    /* string_view�� ������ ��Ʈ���� �����ؼ� �������� ���� �ƴ϶�
       ��Ʈ���� ���� �ִ� �ּҸ� ������ ���縦 ���� �޸� ������ �ִ� ���̺귯��
    */
    using MESH_KEY = std::wstring;
    using FONT_KEY = std::wstring;

    // ���� �̸����� Ű ���� �޾ƿ��⿡ �� 3���� wstring���� ���� ���ϸ� ū��
    using SHADER_KEY  = std::wstring;
    using TEXTURE_KEY = std::wstring;
    using SOUND_KEY   = std::wstring;

    class RendererInterface
    {
    protected:
        virtual void Init()    = 0;
        virtual void Release() = 0;
        virtual void Update()  = 0;
        virtual void Render()  = 0;
    };
}  // namespace HBSoft