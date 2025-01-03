/*
author : 변한빛
description : Precompile header 기능을 사용하기 위해 만든 헤더파일

version: 1.1
date: 2024-12-11
*/

#pragma once
#include <memory>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <string_view>
#include <optional>
#include <functional>
#include <random>
#include <filesystem>
#include <Windows.h>
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <tchar.h>
#include <atlconv.h>

// #ifdef _DEBUG
//  콘솔창 만들기 위해 설정해둔 커멘드
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#include <iostream>
// #endif

// ---------------------------------------
//			    WinCodec
// ---------------------------------------

#include <wincodec.h>
#include <wincodecsdk.h>

// ---------------------------------------
//			    DirectXTK
// ---------------------------------------

#include "DirectXTK/WICTextureLoader.h"
#include "DirectXTK/DDSTextureLoader.h"
#include "DirectXTK/ScreenGrab.h"

// ---------------------------------------
//			      GLM
// ---------------------------------------

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

// ---------------------------------------
//			      FMOD
// ---------------------------------------

#include "fmod/fmod.hpp"

// ---------------------------------------
//			      ImGui
// ---------------------------------------

// imgui는 디버그용
#ifdef _DEBUG
    #include "imgui/imgui_impl_win32.h"
    #include "imgui/imgui_impl_dx11.h"
    #include "imgui/imgui.h"
#endif

// ---------------------------------------
//			  Library load
// ---------------------------------------

#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "dxguid.lib")

#ifdef _DEBUG
    #pragma comment(lib, "debug/DirectXTK/DirectXTK_d.lib")
    #pragma comment(lib, "debug/glm/glm_d.lib")
    #pragma comment(lib, "debug/fmod/fmod_vc.lib")
    #pragma comment(lib, "debug/network/network_d.lib")
    #pragma comment(lib, "debug/imgui/imguid.lib")
#else
    #pragma comment(lib, "release/DirectXTK/DirectXTK_r.lib")
    #pragma comment(lib, "release/glm/glm.lib")
    #pragma comment(lib, "release/fmod/fmod_vc.lib")
    #pragma comment(lib, "release/imgui/imgui.lib")
#endif

// ---------------------------------------
//			Internal Sources
// ---------------------------------------

using namespace Microsoft::WRL;
using namespace glm;

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
#include "Shader/ConstantBuffers.h"
#include "EventHandler.h"
#include "Observer.h"
