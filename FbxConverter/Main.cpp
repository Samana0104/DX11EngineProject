/*
author : 변한빛
description : fbx converter 코드 엔트리 포인트

version: 1.0.5
date: 2024-12-11
*/

#include "HBSLoader.h"
#include "FbxLoader.h"

#ifdef _DEBUG
    #pragma comment(lib, "debug/engine/DX11EngineLib_d.lib")
#else
// release버전은 아직 무리
    #pragma comment(lib, "debug/engine/DX11EngineLib_d.lib")
#endif

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    HBSoft::HBSLoader hbsLoader;
    HBSoft::FbxLoader fbxLoader;

    std::filesystem::path exePath = std::filesystem::current_path();

    std::shared_ptr<HBSoft::Mesh> mesh;

    for (auto& file : std::filesystem::directory_iterator(exePath))
    {
        std::wstring filePath = file.path().wstring();
        if (!file.is_directory())
        {
            auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(filePath);

            if (fileExt.compare(L".fbx") == 0)
            {
                mesh = fbxLoader.Load(std::filesystem::absolute(file.path()).wstring());
                hbsLoader.Export(mesh, exePath.wstring() + L"\\" + fileName + fileExt);
            }
        }
    }


    return 0;
}