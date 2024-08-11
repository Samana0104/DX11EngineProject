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
		std::uint8_t	ioType;	// ��Ŷ ����� ����
		std::uint32_t 	len;	// msg ����Ʈ ũ��
		std::uint16_t	time;   // ��Ŷ ���� �ð� 
		PacketType		type;	// � ��Ŷ�̴�.	
	};

	struct BytePacket
	{
		PacketHeader header;
		char		 msg[PACKET_MSG_SIZE];
	};
#pragma pack(pop)

}
