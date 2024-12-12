/*
author : 변한빛
description : Precompile header 기능을 사용하기 위해 만든 헤더파일

version: 1.1
date: 2024-12-11
*/

#pragma once

#include <fbxsdk.h>
#include "Core.h"

// ---------------------------------------
//			  Library load
// ---------------------------------------

#ifdef _DEBUG
    #pragma comment(lib, "debug/engine/DX11EngineLib_d.lib")
    #pragma comment(lib, "debug/fbxsdk/libfbxsdk-md.lib")
    #pragma comment(lib, "debug/fbxsdk/libxml2-md.lib")
    #pragma comment(lib, "debug/fbxsdk/zlib-md.lib")
#else
    #pragma comment(lib, "release/engine/DX11EngineLib_r.lib")
    #pragma comment(lib, "release/fbxsdk/libfbxsdk-md.lib")
    #pragma comment(lib, "release/fbxsdk/libxml2-md.lib")
    #pragma comment(lib, "release/fbxsdk/zlib-md.lib")
#endif
