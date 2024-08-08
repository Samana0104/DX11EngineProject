#pragma once

using uint_8 = unsigned char;

enum class PacketHeader : uint_8
{
	SERV_CONNECT_SEND,
	SERV_CONNECT_REQUEST,	

};

struct BytePacket
{
	PacketHeader m_header;
};
