#include "pch.h"
#include "FmodSystem.h"
using namespace HBSoft;

FmodSystem::FmodSystem()
{
    if (mFmodSys == nullptr && mRefSysCount == 0)
    {
        if (CreateFmodSystem())
            mRefSysCount = 1;
    }
    else
    {
        mRefSysCount++;
    }
    // OutputDebugString((std::to_wstring(mRefSysCount) + L"\n").c_str());
}

FmodSystem::~FmodSystem()
{
    if (mRefSysCount <= 1)
    {
        DeleteFmodSystem();
        mRefSysCount = 0;
    }
    else
    {
        mRefSysCount--;
    }

    // OutputDebugString((std::to_wstring(mRefSysCount) + L"\n").c_str());
}

bool FmodSystem::CreateFmodSystem()
{
    FMOD_RESULT hr = FMOD::System_Create(&mFmodSys);

    if (hr != FMOD_OK)
    {
        mFmodSys = nullptr;
        return false;
    }

    hr = mFmodSys->init(MAX_CHANNELS, FMOD_INIT_NORMAL, nullptr);

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
    if (mFmodSys != nullptr)
    {
        mFmodSys->close();
        mFmodSys->release();
    }

    // OutputDebugString(L"\nFMOD System Delete\n");
    mFmodSys = nullptr;
}

UINT FmodSystem::GetRefCount() const
{
    return mRefSysCount;
}

FMOD_SYS* const FmodSystem::operator->()
{
    if (mFmodSys == nullptr)
        MessageBoxA(NULL, "Not created fmod system[Pointer error]", "[Fmod System]", MB_OK);

    return mFmodSys;
}
