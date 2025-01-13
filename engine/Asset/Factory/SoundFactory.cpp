/*
author : 변한빛
description : 사운드를 생성 및 FmodSystem를 관리하는 소스파일

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

    // modern c++ 기능인데 구조적 바인딩이라고 pair 객체 바로 변수 값에다 쏴주는 기능임
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
