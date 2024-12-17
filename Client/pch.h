/*
author : ���Ѻ�
description : Precompile header ����� ����ϱ� ���� ���� �������

version: 1.1
date: 2024-12-11
*/

#pragma once

#include "Core.h"

// ---------------------------------------
//			  Library load
// ---------------------------------------

#ifdef _DEBUG
    #pragma comment(lib, "debug/engine/DX11EngineLib_d.lib")
#else
    #pragma comment(lib, "release/engine/DX11EngineLib_r.lib")
#endif

// ---------------------------------------
//			Internal Sources
// ---------------------------------------
