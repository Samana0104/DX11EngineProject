#include "pch.h"
#include "MySpriteHandler.h"
using namespace MyProject;

bool MySpriteHandler::CreateSpriteResource(const wstringV _filePath)
{
	auto fileInfo = MyCoreAPI::GetFileNameAndExt(_filePath);
	auto sprite = std::make_shared<MySprite>();

	if (fileInfo.second.compare(L".sprite") != 0)
		return false;
	
	if (!sprite->LoadScript(_filePath))
		return false;

	SPRITE_KEY key = fileInfo.first + fileInfo.second;
	return AddResource(key, sprite);
}

void MySpriteHandler::CreateSpriteAsFolderPath(const wstringV _folderPath)
{
	std::filesystem::directory_iterator iter(_folderPath);

	while (iter != std::filesystem::end(iter))
	{
		const auto & currentFile = *(iter++);

		if (currentFile.is_directory())
			CreateSpriteAsFolderPath(currentFile.path().wstring());
		else
			CreateSpriteResource(currentFile.path().wstring());
	}
}
