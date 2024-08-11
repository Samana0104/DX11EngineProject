#include "pch.h"
#include "MyNetwork.h"
using namespace MyProject;


MyNetwork::MyNetwork(IPProtocol netProt)
	: m_netProt(netProt)
{
	assert(InitSock());
}

MyNetwork::~MyNetwork()
{
	DelWinSock();
}

bool MyNetwork::InitSock() const noexcept
{
	WSADATA lpWSAData;
	WSAStartup(MAKEWORD(2, 2), &lpWSAData);

	return IsError();
}

bool MyNetwork::DelWinSock() const noexcept
{
	WSACleanup();

	return IsError();
}

//bool MyNetwork::bind() const noexcept
//{
//    inet_pton(AF_INET, "192.168.0.12", &sa.sin_addr.s_addr);
//    sa.sin_port = htons(10000);
//    sa.sin_family = AF_INET;
//    int namelen = sizeof(sa);
//    int ret = bind(g_hListenSock,(sockaddr*)&sa,namelen);
//}

bool MyNetwork::IsError() const noexcept
{
	int error = WSAGetLastError();

	if (error != WSAEWOULDBLOCK)
		return true;

	return false;
}

std::string MyNetwork::GetErrorMsg() const noexcept
{
	if (!IsError())
		return nullptr;

	std::string msg;
	LPVOID		msgErrorBuffer;

	int errorCode = WSAGetLastError();
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		0,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&msgErrorBuffer),
		0,
		NULL
	);
	msg = reinterpret_cast<char*>(msgErrorBuffer);
	LocalFree(msgErrorBuffer);

	return std::move(msg);
}

void MyNetwork::SendPacket()
{
	if (m_netProt == IPProtocol::TCP)
		SendByTCP();
	else if (m_netProt == IPProtocol::UDP)
		SendByUDP();
}

void MyNetwork::RecvPacket()
{
	if (m_netProt == IPProtocol::TCP)
		RecvByTCP();
	else if (m_netProt == IPProtocol::UDP)
		RecvByUDP();
}
void MyNetwork::Run()
{
}

