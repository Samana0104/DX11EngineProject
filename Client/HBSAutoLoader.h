/*
author : ������
description : ������Ʈ �ε� �ڵ�ȭ�� ���� ��� ����
              v 1.1.2 : ���ø�ȭ �߰� �� cpp ������ ����
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
        std::vector<T> objects;  // T ��ü�� ����

        // �������� .hbs ���� �о�� ��ü ���� �� �ʱ�ȭ
        void LoadFromFolder(const std::string& folderPath, std::shared_ptr<Camera> camera);

        // Ư�� �̸����� ��ü �˻�
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
                    objects.emplace_back(fileName);  // T ��ü �߰�
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