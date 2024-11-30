/*
author : 변한빛
description : Precompile header 기능을 사용하기 위해 만든 헤더파일

version: 1.0.5
date: 2024-11-17
*/

#pragma once
#include <memory>
#include <initializer_list>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
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

#ifdef _DEBUG
// 콘솔창 만들기 위해 설정해둔 커멘드
    #pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
    #include <iostream>
#endif

// ---------------------------------------
//			    DirectXTK
// ---------------------------------------

#include "DirectXTK/WICTextureLoader.h"
#include "DirectXTK/DDSTextureLoader.h"

// ---------------------------------------
//			      GLM
// ---------------------------------------

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

// ---------------------------------------
//			      Assimp
// ---------------------------------------

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>

// ---------------------------------------
//			      FMOD
// ---------------------------------------

#include "..\extern\inc\fmod\fmod.hpp"

// ---------------------------------------
//			      ImGui
// ---------------------------------------

// imgui는 디버그용
#ifdef _DEBUG
    #include "imgui.h"
    #include "imgui_impl_win32.h"
    #include "imgui_impl_dx11.h"
#endif

// ---------------------------------------
//			     fbx sdk
// ---------------------------------------

#include <fbxsdk.h>

// ---------------------------------------
//			  Library load
// ---------------------------------------

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d11.lib")

#ifdef _DEBUG
    #pragma comment(lib, "debug/DirectXTK/DirectXTK_d.lib")
    #pragma comment(lib, "debug/glm/glm_d.lib")
    #pragma comment(lib, "debug/imgui/imguid.lib")
    #pragma comment(lib, "debug/fmod/fmod_vc.lib")
    #pragma comment(lib, "debug/network/network_d.lib")
    #pragma comment(lib, "debug/assimp/assimp-vc143-mtd")
    #pragma comment(lib, "debug/fbxsdk/libfbxsdk-md.lib")
    #pragma comment(lib, "debug/fbxsdk/libxml2-md.lib")
    #pragma comment(lib, "debug/fbxsdk/zlib-md.lib")
#else
    #pragma comment(lib, "release/DirectXTK/DirectXTK_r.lib")
    #pragma comment(lib, "release/glm/glm.lib")
    #pragma comment(lib, "release/fmod/fmod_vc.lib")
    #pragma comment(lib, "release/imgui/imgui.lib")
    #pragma comment(lib, "release/assimp/assimp-vc143-mt")
    #pragma comment(lib, "release/fbxsdk/libfbxsdk-md.lib")
    #pragma comment(lib, "release/fbxsdk/libxml2-md.lib")
    #pragma comment(lib, "release/fbxsdk/zlib-md.lib")
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
