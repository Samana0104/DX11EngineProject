#include "pch.h"
#include "SpriteHandler.h"
using namespace HBSoft;

bool SpriteHandler::CreateSpriteResource(const wstringV _filePath)
{
	auto fileInfo = CoreAPI::GetFileNameAndExt(_filePath);
	auto sprite = std::make_shared<Sprite>();

	if (fileInfo.second.compare(L".sprite") != 0)
		return false;
	
	if (!sprite->LoadScript(_filePath))
		return false;

	SPRITE_KEY key = fileInfo.first + fileInfo.second;
	return AddResource(key, sprite);
}

void SpriteHandler::CreateSpriteAsFolderPath(const wstringV _folderPath)
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
