#pragma once
#include "pch.h"

using uint_8 = unsigned char;

enum class PacketHeader : uint_8
{
	SERV_CONNECT_SEND,
	SERV_CONNECT_REQUEST,	
	CHAT_MSG_SEND,
};

const int PACKET_HEADER_SIZE = sizeof(uint_8);
const int PACKET_MSG_SIZE = 1024;

struct BytePacket
{
	PacketHeader m_header;
	BYTE		 m_msg[PACKET_MSG_SIZE];
};
