#include "pch.h"
#include "MySoundHandler.h"
using namespace MyProject;

MySoundHandler::MySoundHandler()
{
	_ASSERT(CreateFmodSystem());
}

bool MySoundHandler::CreateFmodSystem()
{
	if (mFmodSys != nullptr)
		return true;

	FMOD::System* fmodSys;
	FMOD_RESULT hr = FMOD::System_Create(&fmodSys);

	if (hr != FMOD_OK)
		return false;

	hr = fmodSys->init(MAX_CHANNELS, FMOD_INIT_NORMAL, nullptr);

	if (hr != FMOD_OK)
		return false;

	mFmodSys.reset(std::move(fmodSys));

	return true;
}

MySoundHandler::~MySoundHandler()
{
	mFmodSys->close();
	//mFmodSys.release(); // 어째서 이거 없으면 안됨?
}

