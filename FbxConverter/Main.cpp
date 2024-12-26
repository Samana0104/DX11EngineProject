/*
author : 변한빛, 이지혁
description : fbx converter 코드 엔트리 포인트
            : 1.0.6 converter 폴더 파일 정리 및 이동 자동화
            : 1.1.0 material 로딩, skm 로딩 추가

version: 1.1.0
date: 2024-12-26
*/

#include "pch.h"
#include "FbxLoader.h"
#include "SkmLoader.h"

void CleanupAndMoveFiles()
{
    namespace fs = std::filesystem;

    // Visual Studio 환경 변수로부터 현재 프로젝트 경로 가져오기
    // (프로젝트 속성/디버깅/환경에 PROJECT_ROOT=$(ProjectDir) 추가)
    char*  project_root_env = nullptr;
    size_t len              = 0;

    // "PROJECT_ROOT" 환경 변수 가져오기
    if (_dupenv_s(&project_root_env, &len, "PROJECT_ROOT") == 0 && project_root_env != nullptr)
    {
        try
        {
            fs::path project_root = project_root_env;
            fs::current_path(project_root);
        }
        catch (const fs::filesystem_error& e)
        {
            std::cerr << "오류: " << e.what() << std::endl;
        }
    }
    else
        std::cerr << "PROJECT_ROOT 환경 변수가 설정되지 않았습니다." << std::endl;


    // filesystem 의 current_path 를 현재 프로젝트 경로로 설정
    if (project_root_env)
    {
        fs::path project_root = project_root_env;
        fs::current_path(project_root);

        free(project_root_env);
    }
    else
        std::cerr << "PROJECT_ROOT 환경 변수가 설정되지 않았습니다." << std::endl;

    // 프로젝트 폴더 기준 경로
    fs::path fbxConverterPath = fs::current_path();
    fs::path staticObjPath    = fs::current_path().parent_path() / "res" / "Mesh" / "StaticObj";
    fs::path metadataPath     = fs::current_path().parent_path() / "res" / "Mesh" / "Metadata";

    // .fbx 파일 삭제
    for (const auto& file : fs::directory_iterator(fbxConverterPath))
    {
        if (file.path().extension() == ".fbx")
        {
            try
            {
                fs::remove(file.path());
                std::wcout << L"Deleted: " << file.path().wstring() << std::endl;
            }
            catch (const fs::filesystem_error& e)
            {
                std::wcerr << L"Failed to delete: " << file.path().wstring() << L" - " << e.what()
                           << std::endl;
            }
        }
    }

    // .hbs 파일 이동 (res 폴더의 StaticObj 로 이동)
    for (const auto& file : fs::directory_iterator(fbxConverterPath))
    {
        if (file.path().extension() == ".hbs")
        {
            try
            {
                fs::rename(file.path(), staticObjPath / file.path().filename());
                std::wcout << L"Moved .hbs file: " << file.path().wstring() << std::endl;
            }
            catch (const fs::filesystem_error& e)
            {
                std::wcerr << L"Failed to move .hbs file: " << file.path().wstring() << L" - "
                           << e.what() << std::endl;
            }
        }
    }

    // .txt 파일 이동 (res 폴더의 Metadata 로 이동)
    for (const auto& file : fs::directory_iterator(fbxConverterPath))
    {
        if (file.path().extension() == ".txt")
        {
            try
            {
                fs::rename(file.path(), metadataPath / file.path().filename());
                std::wcout << L"Moved .txt file: " << file.path().wstring() << std::endl;
            }
            catch (const fs::filesystem_error& e)
            {
                std::wcerr << L"Failed to move .txt file: " << file.path().wstring() << L" - "
                           << e.what() << std::endl;
            }
        }
    }
}

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

    // 프로그램 종료 직전에 파일 정리 작업 수행
    CleanupAndMoveFiles();

    return 0;
}