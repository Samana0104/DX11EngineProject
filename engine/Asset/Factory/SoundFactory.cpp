/*
author : ���Ѻ�
description : ���带 ���� �� FmodSystem�� �����ϴ� �ҽ�����

version: 1.0.0
date: 2024-11-17
*/
#include "pch.h"
#include "SoundFactory.h"
using namespace HBSoft;

void SoundFactory::InitFmodSystem()
{
    FMOD_RESULT hr = FMOD::System_Create(&m_fmodSys);
    m_fmodSys->setSoftwareFormat(4'4100, FMOD_SPEAKERMODE_STEREO, 0);
    m_fmodSys->init(32, FMOD_INIT_NORMAL, 0);

    hr = m_fmodSys->init(MAX_CHANNELS, FMOD_INIT_NORMAL, nullptr);

    if (hr != FMOD_OK)
        assert(false);
}

void SoundFactory::ReleaseFmodSystem()
{
    m_fmodSys->close();
    m_fmodSys->release();
}

std::shared_ptr<HSound> SoundFactory::Create(wstringV path)
{
    if (m_fmodSys == nullptr)
        InitFmodSystem();

    // modern c++ ����ε� ������ ���ε��̶�� pair ��ü �ٷ� ���� ������ ���ִ� �����
    auto sound = std::make_shared<HSound>(m_fmodSys, path);
    return sound;
}

bool SoundFactory::IsSoundFormat(const wstringV ext)
{
    if (ext.compare(L".mp3") == 0)
        return true;
    else if (ext.compare(L".wav") == 0)
        return true;

    return false;
}
