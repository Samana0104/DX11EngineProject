#pragma once
#include "pch.h"

namespace MyProject
{
	enum class PacketHeader : uint_8
	{
		SERV_CONNECT_SEND,
		SERV_CONNECT_REQUEST,
		CHAT_MSG,
	};

	const int PACKET_HEADER_SIZE = sizeof(uint_8);
	const int PACKET_MSG_SIZE = 1024;

	struct BytePacket
	{
		PacketHeader m_header;
		std::array<BYTE, PACKET_MSG_SIZE> m_msg;
	};
}
