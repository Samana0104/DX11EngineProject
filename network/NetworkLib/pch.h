#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <string>
#include <string_view>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <cassert>
#include <array>
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
#include "MySession.h"

// -----------------------------------
//			Libraries
// -----------------------------------
#pragma comment(lib,"ws2_32.lib")


// -----------------------------------
//			Define
// -----------------------------------

namespace HBSoft
{
	using stringV = std::string_view;
	using PORT	  = short;
	using PACKET  = unsigned char;
	using ConditionV = std::condition_variable;
}


