#include "pch.h"
#include "MyTextureHandler.h"
using namespace MyProject;

bool MyTextureHandler::CreateTextureComponent(
	const wstringV _texturePath)
{
	std::wstring key = GetKeyAsFileName(_texturePath);

	auto texture = std::make_shared<MyTexture>(_texturePath);
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
			CreateTextureComponent(currentFile.path().wstring());
	}
}


