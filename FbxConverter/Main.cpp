/*
author : 변한빛
description : fbx converter 코드 엔트리 포인트

version: 1.0.5
date: 2024-12-23
*/

#include "pch.h"
#include "FbxLoader.h"
#include "SkmLoader.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    HBSoft::HBSLoader hbsLoader;
    HBSoft::FbxLoader fbxLoader;
    HBSoft::SkmLoader skmLoader;

    std::filesystem::path exePath = std::filesystem::current_path();

    std::vector<std::shared_ptr<HBSoft::AnimationClip>> animations;

    for (auto& file : std::filesystem::directory_iterator(exePath))
    {
        std::wstring filePath = file.path().wstring();
        if (!file.is_directory())
        {
            auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(filePath);

            if (fileExt.compare(L".fbx") == 0)
            {
                std::shared_ptr<HBSoft::Mesh> mesh = std::make_shared<HBSoft::Mesh>();
                fbxLoader.Load(std::filesystem::absolute(file.path()).wstring(), mesh, animations);
                hbsLoader.Export(mesh, filePath);

                for (size_t i = 0; i < animations.size(); i++)
                    skmLoader.Export(animations[i], filePath);

                animations.clear();
            }
        }
    }


    return 0;
}