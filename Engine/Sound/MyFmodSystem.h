#pragma once
#include "MyCoreAPI.h"

/*
	FMOD SYSTEM SMART POINTER
*/

namespace MyProject
{
	using FMOD_SYS = FMOD::System;

	class MyFmodSystem
	{
	private:
		inline static const int  MAX_CHANNELS = 32;

		inline static UINT		 mRefSysCount = 0;
		inline static FMOD_SYS * mFmodSys	  = nullptr;

	private:
		bool CreateFmodSystem();
		void DeleteFmodSystem();

		MyFmodSystem(const MyFmodSystem&) = delete;
		MyFmodSystem(MyFmodSystem&&) = delete;
		MyFmodSystem& operator=(MyFmodSystem&&) = delete;
		MyFmodSystem& operator=(const MyFmodSystem&) = delete;

	public:
		MyFmodSystem();
		~MyFmodSystem();

		UINT GetRefCount() const;
		FMOD_SYS* const operator->();

	};
}

