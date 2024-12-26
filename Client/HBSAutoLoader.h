/*
author : ������
description : ������Ʈ �ε� �ڵ�ȭ�� ���� ��� ����
              v 1.1.2 : ���ø�ȭ �߰� �� cpp ������ ����
              v 1.1.3 : ���ø����� ���� Ÿ���� �˻��Ͽ� Static3DObj �� �� TransformType �� �������ִ� �ڵ�ȭ �ڵ� �߰�
version: 1.1.3
date: 2024-12-24
*/
#pragma once

namespace HBSoft
{
    template <typename T>
    class HBSAutoLoader
    {
    public:
        std::vector<T> HBSContainer;  // T ��ü�� ����

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
            // ���ø����� ���� Ÿ���� Static3DObj �� �� ������ �ε��ϸ鼭 TransformType �� ��������
            // Ư�� Ÿ���� ������Ʈ�� �ε�� �� �б� ó���� �ʿ��ϸ� �� ���ǹ� �ؿ� ������ �߰��ϸ� ��
            if constexpr (std::is_same<T, Static3DObj>::value) // C++ 17 ���� �߰��� ���, ������ Ÿ�ӿ��� ������ Ȯ���ϰ� �ش� ���ǿ� �´� �б⸦ ������
            {
                for (const auto& entry : fs::directory_iterator(folderPath))
                {
                    if (entry.is_regular_file() && entry.path().extension() == ".hbs")
                    {
                        std::string fileName = entry.path().filename().string();
                        HBSContainer.emplace_back(fileName);  // T ��ü �߰�
                        HBSContainer.back().Init(
                        std::wstring().assign(fileName.begin(), fileName.end()));
                        HBSContainer.back().SetCamera(camera);
                        if (fileName.find('#') == 0)
                            HBSContainer.back().SetTransType(TransformType::UnityTrans);
                        else
                            HBSContainer.back().SetTransType(TransformType::GooseGameTrans);
                    }
                }
            }
            else
            {
                for (const auto& entry : fs::directory_iterator(folderPath))
                {
                    if (entry.is_regular_file() && entry.path().extension() == ".hbs")
                    {
                        std::string fileName = entry.path().filename().string();
                        HBSContainer.emplace_back(fileName);  // T ��ü �߰�
                        HBSContainer.back().Init(
                        std::wstring().assign(fileName.begin(), fileName.end()));
                        HBSContainer.back().SetCamera(camera);
                    }
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

    // ���� �̸��� ���� Ư�� ������Ʈ �ν��Ͻ��� ����
    template <typename T>
    T* HBSAutoLoader<T>::FindByName(const std::string& name)
    {
        for (auto& obj : HBSContainer)
        {
            if (obj.GetName() == name)
            {
                return &obj;
            }
        }
        return nullptr;
    }
}  // namespace HBSoft