/*
author : 변한빛
description : 사운드 전체를 매니징 하기 위해 만든 소스 파일

version: 1.0.0
date: 2024-11-04
*/

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
