/*
author : 변한빛
description : Precompile header 기능을 사용하기 위해 만든 헤더파일

version: 1.0.3
date: 2024-11-12
*/

#pragma once
#include <memory>
#include <initializer_list>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <set>
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

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "fmod/fmod.hpp"
#include "DirectXTK/WICTextureLoader.h"

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "fmod/fmod_vc.lib")

#ifdef _DEBUG
    #pragma comment(lib, "DirectXTK/DirectXTK_d.lib")
    #pragma comment(lib, "glm/glm_d.lib")
    #pragma comment(lib, "imgui/imguid.lib")
    #pragma comment(lib, "network/network_d.lib")
    #pragma comment(lib, "assimp/assimp-vc143-mtd")
#else
    #pragma comment(lib, "DirectXTK/DirectXTK_r.lib")
    #pragma comment(lib, "glm/glm.lib")
    #pragma comment(lib, "imgui/imgui.lib")
    #pragma comment(lib, "assimp/assimp-vc143-mt")
#endif

// ---------------------------------------
//			Internal Sources
// ---------------------------------------

using namespace Microsoft::WRL;
using namespace glm;

// imgui는 디버그용
#ifdef _DEBUG
    #include "imgui.h"
    #include "imgui_impl_win32.h"
    #include "imgui_impl_dx11.h"
#endif

#include "MgrTemplate.h"
#include "SystemTimer.h"
#include "HRect.h"
#include "HPoint.h"
#include "Window.h"
#include "D3Device.h"
#include "Input.h"
#include "CoreAPI.h"
#include "Singleton.h"
#include "Scene.h"
#include "ConstantBuffers.h"
#include "EventHandler.h"
#include "Observer.h"
