#pragma once
#include <memory>
#include <initializer_list>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <chrono>
#include <string_view>
#include <unordered_map>
#include <optional>
#include <functional>
#include <Windows.h>
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <tchar.h>
#include <glm/glm.hpp>
#include "directxtk/WICTextureLoader.h"
#include "Singleton.h"
#include "MyWindow.h"
#include "D3Device.h"

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "d3d11.lib")
