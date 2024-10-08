#pragma once

#include "pch.h"
#include "MyPacket.h"

namespace HBSoft
{
	struct Session
	{
		sockaddr_in addr;
		SOCKET		sock;
		bool		isConnecting;
		MyPacket  packet;
	};

	class SessionManager
	{
	private:
		inline static uint64_t		m_sessionNumber = 0;
		std::map<uint64_t, Session> m_sessions;
		
	public:
		void Add(SOCKET sock, sockaddr_in& addr);
		void Disconnect();
	};
}

