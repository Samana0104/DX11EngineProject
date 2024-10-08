#include "pch.h"
#include "TextureHandler.h"
using namespace HBSoft;

bool TextureHandler::CreateTextureResource(const wstringV _filePath)
{
    auto fileInfo = CoreAPI::GetFileNameAndExt(_filePath);

    if (fileInfo.second.compare(L".png") != 0 && fileInfo.second.compare(L".jpg") != 0 &&
        fileInfo.second.compare(L".bmp") != 0)
        return false;

    TEXTURE_KEY key     = fileInfo.first + fileInfo.second;
    auto        texture = std::make_shared<Texture>(_filePath);
    return AddResource(key, texture);
}

void TextureHandler::CreateTextureAsFolderPath(const wstringV _folderPath)
{
    std::filesystem::directory_iterator iter(_folderPath);

    while (iter != std::filesystem::end(iter))
    {
        const auto& currentFile = *(iter++);

        if (currentFile.is_directory())
            CreateTextureAsFolderPath(currentFile.path().wstring());
        else
            CreateTextureResource(currentFile.path().wstring());
    }
}
