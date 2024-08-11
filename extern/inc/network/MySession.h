#pragma once

#include "pch.h"

namespace MyProject
{
	struct IOCPSession
	{
		sockaddr_in addr;
		SOCKET		sock;
		PORT		port;
		bool		isConnecting;
	};
}

