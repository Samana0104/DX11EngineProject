/*
author : ���Ѻ�
description : ���� ��ü�� �����ϱ� ���� ���� ��� ����

version: 1.0.0
date: 2024-11-04
*/

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
