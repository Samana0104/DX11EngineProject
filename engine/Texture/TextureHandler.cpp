#include "pch.h"
#include "TextureHandler.h"
using namespace HBSoft;

bool TextureHandler::CreateTextureResource(const wstringV filePath)
{
    auto fileInfo = CoreAPI::GetFileNameAndExt(filePath);

    if (fileInfo.second.compare(L".png") != 0 && fileInfo.second.compare(L".jpg") != 0 &&
        fileInfo.second.compare(L".bmp") != 0)
        return false;

    TEXTURE_KEY key     = fileInfo.first + fileInfo.second;
    auto        texture = std::make_shared<Texture>(filePath);
    return Add(key, texture);
}

void TextureHandler::CreateTextureAsFolderPath(const wstringV folderPath)
{
    std::filesystem::directory_iterator iter(folderPath);

    while (iter != std::filesystem::end(iter))
    {
        const auto& currentFile = *(iter++);

        if (currentFile.is_directory())
            CreateTextureAsFolderPath(currentFile.path().wstring());
        else
            CreateTextureResource(currentFile.path().wstring());
    }
}
