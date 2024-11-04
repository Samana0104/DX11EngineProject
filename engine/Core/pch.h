/*
author : 변한빛
description : Precompile header 기능을 사용하기 위해 만든 헤더파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include <memory>
#include <initializer_list>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <list>
#include <algorithm>
#include <chrono>
#include <string_view>
#include <optional>
#include <functional>
#include <tuple>
#include <random>
#include <filesystem>
#include <Windows.h>
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <tchar.h>
#include <atlconv.h>
#include "glm/glm.hpp"
#include "fmod/fmod.hpp"
#include "DirectXTK/WICTextureLoader.h"

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "winmm.lib")

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "fmod/fmod_vc.lib")
#pragma comment(lib, "glm/glm.lib")

#ifdef _DEBUG
    #pragma comment(lib, "DirectXTK/DirectXTK_d.lib")
#else
    #pragma comment(lib, "DirectXTK/DirectXTK_r.lib")
#endif

// ---------------------------------------
//			Internal Sources
// ---------------------------------------

using namespace Microsoft::WRL;

#include "CoreAPI.h"
#include "Singleton.h"
#include "Window.h"
#include "D3Device.h"
#include "MgrTemplate.h"
