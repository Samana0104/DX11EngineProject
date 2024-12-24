/*
author : 이지혁
description : 오브젝트 로드 자동화를 위한 소스  파일

version: 1.1.1
date: 2024-12-24
*/
#include "pch.h"
#include "HBSAutoLoader.h"

using namespace HBSoft;

void HBSAutoLoader::LoadFromFolder(const std::string& folderPath, std::shared_ptr<Camera> camera)
{
    {
        namespace fs = std::filesystem;

        try
        {
            for (const auto& entry : fs::directory_iterator(folderPath))
            {
                if (entry.is_regular_file() && entry.path().extension() == ".hbs")
                {
                    std::string fileName = entry.path().filename().string();
                    objects.emplace_back(fileName);  // 객체 추가
                    objects.back().Init(
                    std::wstring().assign(fileName.begin(), fileName.end()));
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
}

Static3DObj* HBSAutoLoader::FindByName(const std::string& name)
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
