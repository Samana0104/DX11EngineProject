#include "pch.h"
#include "SoundHandler.h"
using namespace HBSoft;

bool SoundHandler::CreateSoundResource(const wstringV _filePath)
{
	auto fileInfo = CoreAPI::GetFileNameAndExt(_filePath);

	//if (fileInfo.second.compare(L"png") != 0 && 
	//	fileInfo.second.compare(L"jpg") != 0 &&
	//	fileInfo.second.compare(L"bmp") != 0)
	//	return;

	SOUND_KEY key = fileInfo.first + fileInfo.second;

	auto sound = std::make_shared<Sound>(_filePath);
	return AddResource(key, sound);
}

void SoundHandler::CreateSoundAsFolderPath(const wstringV _folderPath)
{
	std::filesystem::directory_iterator iter(_folderPath);

	while (iter != std::filesystem::end(iter))
	{
		const auto & currentFile = *(iter++);

		if (currentFile.is_directory())
			CreateSoundAsFolderPath(currentFile.path().wstring());
		else
			CreateSoundResource(currentFile.path().wstring());
	}
}

void SoundHandler::Update()
{
	auto& allResource = GetAllResources();
	for (auto& sound : allResource)
		sound.second->Update();
}



