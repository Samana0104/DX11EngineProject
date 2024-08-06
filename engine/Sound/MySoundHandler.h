#pragma once
#include "ResourceHandler.h"
#include "MySound.h"

namespace MyProject
{
	class MySoundHandler : public ResourceHandler<MySound, SOUND_KEY>
	{
	private:

	public:
		bool CreateSoundResource(const wstringV _filePath);
		void CreateSoundAsFolderPath(const wstringV _folderPath);
		void Update();
	};
}
