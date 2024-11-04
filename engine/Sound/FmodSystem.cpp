#include "pch.h"
#include "FmodSystem.h"
using namespace HBSoft;

FmodSystem::FmodSystem()
{
    if (m_fmodSys == nullptr && m_refSysCount == 0)
    {
        if (CreateFmodSystem())
            m_refSysCount = 1;
    }
    else
    {
        m_refSysCount++;
    }
    // OutputDebugString((std::to_wstring(m_refSysCount) + L"\n").c_str());
}

FmodSystem::~FmodSystem()
{
    if (m_refSysCount <= 1)
    {
        DeleteFmodSystem();
        m_refSysCount = 0;
    }
    else
    {
        m_refSysCount--;
    }

    // OutputDebugString((std::to_wstring(m_refSysCount) + L"\n").c_str());
}

bool FmodSystem::CreateFmodSystem()
{
    FMOD_RESULT hr = FMOD::System_Create(&m_fmodSys);

    if (hr != FMOD_OK)
    {
        m_fmodSys = nullptr;
        return false;
    }

    hr = m_fmodSys->init(MAX_CHANNELS, FMOD_INIT_NORMAL, nullptr);

    if (hr != FMOD_OK)
    {
        DeleteFmodSystem();
        return false;
    }

    // OutputDebugString(L"\nFMOD System Create\n");
    return true;
}

void FmodSystem::DeleteFmodSystem()
{
    if (m_fmodSys != nullptr)
    {
        m_fmodSys->close();
        m_fmodSys->release();
    }

    // OutputDebugString(L"\nFMOD System Delete\n");
    m_fmodSys = nullptr;
}

UINT FmodSystem::GetRefCount() const
{
    return m_refSysCount;
}

FMOD_SYS* const FmodSystem::operator->()
{
    if (m_fmodSys == nullptr)
        MessageBoxA(NULL, "Not created fmod system[Pointer error]", "[Fmod System]", MB_OK);

    return m_fmodSys;
}
