#pragma once

#include "pch.h"
#include "MyPacket.h"

namespace MyProject
{
	struct Session
	{
		sockaddr_in addr;
		SOCKET		sock;
		bool		isConnecting;
		BytePacket  packet;
	};

	struct IOCPSession : Session
	{
	};
}

