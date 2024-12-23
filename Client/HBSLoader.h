#pragma once

#include "3D/Static3DObj.h"

namespace HBSoft
{
    class HBSLoader
    {
    public:
        std::vector<Static3DObj> objects;  // Static3DObj 객체를 저장

        // 폴더에서 .hbs 파일 읽어와 객체 생성 및 초기화
        void LoadFromFolder(const std::string& folderPath);

        // 특정 이름으로 객체 검색
        Static3DObj* FindByName(const std::wstring& name);
    };
}  // namespace HBSoft