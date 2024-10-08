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
    /* string_view는 기존의 스트링을 복사해서 가져오는 것이 아니라
       스트링이 갖고 있는 주소만 가져와 복사를 안해 메모리 이점이 있는 라이브러리
    */
    using MESH_KEY = std::wstring;
    using FONT_KEY = std::wstring;

    // 파일 이름으로 키 값을 받아오기에 이 3개는 wstring으로 선언 안하면 큰일
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