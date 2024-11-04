#pragma once
#include "MgrTemplate.h"
#include "Sound.h"

namespace HBSoft
{
    class SoundHandler : public MgrTemplate<Sound, SOUND_KEY>
    {
    private:

    public:
        bool CreateSoundResource(const wstringV _filePath);
        void CreateSoundAsFolderPath(const wstringV _folderPath);
        void Update();
    };
}  // namespace HBSoft
