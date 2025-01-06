/*
author : 이지혁
description : 오브젝트 로드 자동화를 위한 헤더 파일
              v 1.1.2 : 템플릿화 추가 및 cpp 구현부 통합
              v 1.1.3 : 템플릿으로 들어온 타입을 검사하여 Static3DObj 일 때 TransformType 을 지정해주는
자동화 코드 추가 version: 1.1.3 date: 2024-12-24
*/
#pragma once

namespace HBSoft
{
    template <typename T>
    class HBSAutoLoader
    {
    public:
        std::vector<T> HBSContainer;  // T 객체를 저장

        // 폴더에서 .hbs 파일 읽어와 객체 생성 및 초기화
        void LoadFromFolder(const std::string& folderPath, std::shared_ptr<Camera> camera,
                            std::shared_ptr<DirectionalLight>);

        // 특정 이름으로 객체 검색
        T FindByName(const std::string& name);
    };

    template <typename T>
    void HBSAutoLoader<T>::LoadFromFolder(const std::string& folderPath, std::shared_ptr<Camera> camera,
                                          std::shared_ptr<DirectionalLight> light)
    {
        namespace fs = std::filesystem;

        try
        {
            // 템플릿으로 들어온 타입이 Static3DObj 일 때 파일을 로드하면서 TransformType 을 지정해줌
            // 특정 타입의 오브젝트가 로드될 때 분기 처리가 필요하면 이 조건문 밑에 조건을 추가하면 됨
            if constexpr (std::is_same<T, std::shared_ptr<Static3DObj>>::value)  // C++ 17 부터 추가된 기능, 컴파일
                                                                                 // 타임에서 조건을 확인하고 해당 조건에
                                                                                 // 맞는 분기를 선택함
            {
                for (const auto& entry : fs::directory_iterator(folderPath))
                {
                    if (entry.is_regular_file() && entry.path().extension() == ".hbs")
                    {
                        std::string fileName = entry.path().filename().string();
                        HBSContainer.push_back(std::make_shared<Static3DObj>(fileName));  // T 객체 추가
                        HBSContainer.back()->Init(fileName);
                        HBSContainer.back()->SetCamera(camera);
                        HBSContainer.back()->SetLight(light);
                    }
                }
            }
            else if constexpr (std::is_same<T, std::shared_ptr<Dynamic3DObj>>::value)  
            {
                for (const auto& entry : fs::directory_iterator(folderPath))
                {
                    if (entry.is_regular_file() && entry.path().extension() == ".hbs")
                    {
                        std::string fileName = entry.path().filename().string();
                        HBSContainer.push_back(std::make_shared<Dynamic3DObj>(fileName));  // T 객체 추가
                        HBSContainer.back()->Init(fileName);
                        HBSContainer.back()->SetCamera(camera);
                        HBSContainer.back()->SetLight(light);
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
                        HBSContainer.push_back(std::make_shared<Static3DObj>(fileName));  // T 객체 추가
                        HBSContainer.back()->Init(
                        std::wstring().assign(fileName.begin(), fileName.end()));
                        HBSContainer.back()->SetCamera(camera);
                        HBSContainer.back()->SetLight(light);
                    }
                }
            }
        }
        catch (const std::filesystem::filesystem_error& e)
        {
#ifdef _DEBUG
            std::cerr << "Filesystem error: " << e.what() << std::endl;
#endif
        }
        catch (const std::exception& e)
        {
#ifdef _DEBUG
            std::cerr << "General error: " << e.what() << std::endl;
#endif
        }
    }

    // 파일 이름을 통해 특정 오브젝트 인스턴스에 접근
    template <typename T>
    T HBSAutoLoader<T>::FindByName(const std::string& name)
    {
        for (auto& obj : HBSContainer)
        {
            if (obj->GetName() == name)
            {
                return obj;
            }
        }
        return nullptr;
    }
}  // namespace HBSoft