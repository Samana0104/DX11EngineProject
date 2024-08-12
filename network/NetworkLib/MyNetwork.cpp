#include "pch.h"
#include "MyNetwork.h"
using namespace MyProject;


MyNetwork::MyNetwork()
{
	assert(!InitWinSock());
}

MyNetwork::~MyNetwork()
{
	DelWinSock();
}

bool MyNetwork::InitWinSock() const noexcept
{
	int errorCode;
	WSADATA lpWSAData;
	errorCode = WSAStartup(MAKEWORD(2, 2), &lpWSAData);

	return IsError(errorCode);
}

bool MyNetwork::DelWinSock() const noexcept
{
	int errorCode;
	errorCode = WSACleanup();

	return IsError(errorCode);
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
	int errorCode = WSAGetLastError();
	return IsError(errorCode);
}

bool MyNetwork::IsError(int errorCode) const noexcept
{
	switch (errorCode)
	{
	case WSAEWOULDBLOCK: 
		[[fallthrough]];
	case NO_ERROR:
		return false;
	}

	return true;
}

std::string MyNetwork::GetErrorMsg(int errorCode) const noexcept
{
	std::string msg;
	LPVOID		msgErrorBuffer;

	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&msgErrorBuffer),
		0,
		NULL
	);
	msg = reinterpret_cast<char*>(msgErrorBuffer);
	LocalFree(msgErrorBuffer);

	return std::move(msg);
}

