#pragma once
#include <Windows.h>
#include <string>
#include <string_view>
#include <thread>
#include <memory>
#include <cassert>
#include <array>
#include <cassert>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <atlconv.h> // A2W

// -----------------------------------
//			Containers
// -----------------------------------
#include <map>
#include <vector>
#include <list>
#include <string>
#include <map>

// -----------------------------------
//			My works
// -----------------------------------
#include "MyPacket.h"

// -----------------------------------
//			Libraries
// -----------------------------------
#pragma comment(lib,"ws2_32.lib")


// -----------------------------------
//			Define
// -----------------------------------

namespace MyProject
{
	using uint_8 = unsigned char;
}


