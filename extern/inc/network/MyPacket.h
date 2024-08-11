#pragma once

#include <stdint.h>

namespace MyProject
{
	enum class PacketType : std::uint8_t
	{
		SERV_CONNECT_SEND,
		SERV_CONNECT_REQUEST,
		CHAT_MSG
	};

	const int PACKET_HEADER_SIZE = sizeof(PacketType);
	const int PACKET_MSG_SIZE = 1024;

#pragma pack(push, 1)
	__declspec(align(64)) struct PacketHeader
	{
		std::uint8_t	ioType;	// 패킷 입출력 종류
		std::uint32_t 	len;	// msg 바이트 크기
		std::uint16_t	time;   // 패킷 전송 시간 
		PacketType		type;	// 어떤 패킷이다.	
	};

	struct BytePacket
	{
		PacketHeader header;
		char		 msg[PACKET_MSG_SIZE];
	};
#pragma pack(pop)

}
