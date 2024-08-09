#pragma once

#include "pch.h"

namespace MyProject
{
	struct MySession
	{
		SOCKET		m_sock;
		sockaddr_in m_addr;
	};
}

