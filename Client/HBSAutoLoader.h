/*
author : 이지혁
description : 오브젝트 로드 자동화를 위한 헤더 파일
              v 1.1.2 : 템플릿화 추가 및 cpp 구현부 통합
version: 1.1.2
date: 2024-12-24
*/
#pragma once

#include "3D/Static3DObj.h"

namespace HBSoft
{
    template <typename T>
    class HBSAutoLoader
    {
    public:
        std::vector<T> objects;  // T 객체를 저장

        // 폴더에서 .hbs 파일 읽어와 객체 생성 및 초기화
        void LoadFromFolder(const std::string& folderPath, std::shared_ptr<Camera> camera);

        // 특정 이름으로 객체 검색
        T* FindByName(const std::string& name);
    };

    template <typename T>
    void HBSAutoLoader<T>::LoadFromFolder(const std::string& folderPath, std::shared_ptr<Camera> camera)
    {
        namespace fs = std::filesystem;

        try
        {
            for (const auto& entry : fs::directory_iterator(folderPath))
            {
                if (entry.is_regular_file() && entry.path().extension() == ".hbs")
                {
                    std::string fileName = entry.path().filename().string();
                    objects.emplace_back(fileName);  // T 객체 추가
                    objects.back().Init(std::wstring().assign(fileName.begin(), fileName.end()));
                    objects.back().SetCamera(camera);
                }
            }
        }
        catch (const std::filesystem::filesystem_error& e)
        {
            std::cerr << "Filesystem error: " << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "General error: " << e.what() << std::endl;
        }
    }

    template <typename T>
    T* HBSAutoLoader<T>::FindByName(const std::string& name)
    {
        for (auto& obj : objects)
        {
            if (obj.name == name)
            {
                return &obj;
            }
        }
        return nullptr;
    }
}  // namespace HBSoft