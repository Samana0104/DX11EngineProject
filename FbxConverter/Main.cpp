/*
author : ���Ѻ�, ������
description : fbx converter �ڵ� ��Ʈ�� ����Ʈ
            : 1.0.6 converter ���� ���� ���� �� �̵� �ڵ�ȭ
            : 1.1.0 material �ε�, skm �ε� �߰�

version: 1.1.0
date: 2024-12-26
*/

#include "pch.h"
#include "FbxLoader.h"
#include "SkmLoader.h"

void CleanupAndMoveFiles()
{
    namespace fs = std::filesystem;

    // Visual Studio ȯ�� �����κ��� ���� ������Ʈ ��� ��������
    // (������Ʈ �Ӽ�/�����/ȯ�濡 PROJECT_ROOT=$(ProjectDir) �߰�)
    char*  project_root_env = nullptr;
    size_t len              = 0;

    // "PROJECT_ROOT" ȯ�� ���� ��������
    if (_dupenv_s(&project_root_env, &len, "PROJECT_ROOT") == 0 && project_root_env != nullptr)
    {
        try
        {
            fs::path project_root = project_root_env;
            fs::current_path(project_root);
        }
        catch (const fs::filesystem_error& e)
        {
            std::cerr << "����: " << e.what() << std::endl;
        }
    }
    else
        std::cerr << "PROJECT_ROOT ȯ�� ������ �������� �ʾҽ��ϴ�." << std::endl;


    // filesystem �� current_path �� ���� ������Ʈ ��η� ����
    if (project_root_env)
    {
        fs::path project_root = project_root_env;
        fs::current_path(project_root);

        free(project_root_env);
    }
    else
        std::cerr << "PROJECT_ROOT ȯ�� ������ �������� �ʾҽ��ϴ�." << std::endl;

    // ������Ʈ ���� ���� ���
    fs::path fbxConverterPath = fs::current_path();
    fs::path staticObjPath    = fs::current_path().parent_path() / "res" / "Mesh" / "StaticObj";
    fs::path metadataPath     = fs::current_path().parent_path() / "res" / "Mesh" / "Metadata";

    // .fbx ���� ����
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

    // .hbs ���� �̵� (res ������ StaticObj �� �̵�)
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

    // .txt ���� �̵� (res ������ Metadata �� �̵�)
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

    // ���α׷� ���� ������ ���� ���� �۾� ����
    CleanupAndMoveFiles();

    return 0;
}