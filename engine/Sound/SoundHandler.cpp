#include "pch.h"
#include "SoundHandler.h"
using namespace HBSoft;

bool SoundHandler::CreateSoundResource(const wstringV filePath)
{
    auto fileInfo = HBSoft::GetFileNameAndExt(filePath);

    // if (fileInfo.second.compare(L"png") != 0 &&
    //	fileInfo.second.compare(L"jpg") != 0 &&
    //	fileInfo.second.compare(L"bmp") != 0)
    //	return;

    SOUND_KEY key = fileInfo.first + fileInfo.second;

    auto sound = std::make_unique<Sound>(filePath);
    return Add(key, std::move(sound));
}

void SoundHandler::CreateSoundAsFolderPath(const wstringV folderPath)
{
    std::filesystem::directory_iterator iter(folderPath);

    while (iter != std::filesystem::end(iter))
    {
        const auto& currentFile = *(iter++);

        if (currentFile.is_directory())
            CreateSoundAsFolderPath(currentFile.path().wstring());
        else
            CreateSoundResource(currentFile.path().wstring());
    }
}

void SoundHandler::Update()
{
    auto& allResource = GetAll();
    for (auto& sound : allResource)
        sound.second->Update();
}
