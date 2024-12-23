#include "pch.h"
#include "HBSLoader.h"

using namespace HBSoft;

void HBSLoader::LoadFromFolder(const std::string& folderPath)
{
    try
    {
        for (const auto& entry : std::filesystem::directory_iterator(folderPath))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".hbs")
            {
                std::string fileName = entry.path().filename().string();
                objects.emplace_back(fileName);  // °´Ã¼ Ãß°¡
                objects.back().Init(
                std::wstring().assign(entry.path().string().begin(), entry.path().string().end()));
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

Static3DObj* HBSLoader::FindByName(const std::wstring& name)
{
    for (auto& obj : objects)
    {
        if (obj.name == std::string().assign(name.begin(), name.end()))
        {
            return &obj;
        }
    }
    return nullptr;
}