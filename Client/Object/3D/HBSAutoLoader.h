/*
author : 이지혁
description : 오브젝트 로드 자동화를 위한 헤더 파일

version: 1.1.0
date: 2024-12-23
*/
#pragma once

#include "3D/Static3DObj.h"

namespace HBSoft
{
    class HBSAutoLoader
    {
    public:
        std::vector<Static3DObj> objects;  // Static3DObj 객체를 저장

        // 폴더에서 .hbs 파일 읽어와 객체 생성 및 초기화
        void LoadFromFolder(const std::string& folderPath, std::shared_ptr<Camera> camera);

        // 특정 이름으로 객체 검색
        Static3DObj* FindByName(const std::string& name);
    };
}  // namespace HBSoft