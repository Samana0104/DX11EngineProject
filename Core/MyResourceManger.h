#pragma once
#include "MyTextureHandler.h"
#include "MyMeshHandler.h"
#include "MyFontHandler.h"

namespace MyProject
{
	class MyResourceManager : public Singleton<MyResourceManager>
	{
	private:
		MyTextureHandler mTextureHandler;
		MyMeshHandler	 mMeshHandler;
		MyFontHandler	 mFontHandler;

	public:
		
	};
}

