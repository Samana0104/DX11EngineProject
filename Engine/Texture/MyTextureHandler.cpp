#include "pch.h"
#include "MyTextureHandler.h"
using namespace MyProject;

bool MyTextureHandler::CreateTextureResource(
	const wstringV _filePath)
{
	std::wstring key = GetKeyAsFileName(_filePath);

	auto texture = std::make_shared<MyTexture>(_filePath);
	return AddResource(key, texture);
}

void MyTextureHandler::CreateTextureAsFolderPath(const wstringV _folderPath)
{
	std::filesystem::directory_iterator iter(_folderPath);

	while (iter != std::filesystem::end(iter))
	{
		const auto & currentFile = *(iter++);

		if (currentFile.is_directory())
			CreateTextureAsFolderPath(currentFile.path().wstring());
		else
			CreateTextureResource(currentFile.path().wstring());
	}
}


