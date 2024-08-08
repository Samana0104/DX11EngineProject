#pragma once

using uint_8 = unsigned char;

enum class PacketHeader : uint_8
{
	
};

struct BytePacket
{
	PacketHeader m_header;
};
