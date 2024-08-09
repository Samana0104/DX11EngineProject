#include "pch.h"
#include "MyNetwork.h"
using namespace MyProject;

bool MyNetwork::InitSock()
{
	WSADATA lpWSAData;
	WSAStartup(MAKEWORD(2, 2), &lpWSAData);

	return IsError();
}

bool MyNetwork::DelWinSock()
{
	WSACleanup();

	return IsError();
}

MyNetwork::MyNetwork()
{
	assert(InitSock());
}

MyNetwork::~MyNetwork()
{
	DelWinSock();
	closesocket(m_sock);
}

void MyNetwork::Recv() const
{
}

void MyNetwork::Send()
{
}

void MyNetwork::Accept()
{
}

void MyNetwork::Disconnet()
{
}

void MyNetwork::Run()
{
}

bool MyNetwork::IsError() const
{
	int error = WSAGetLastError();

	if (error != WSAEWOULDBLOCK)
		return true;

	return false;
}

std::string MyNetwork::GetErrorMsg()
{
	if (!IsError)
		return nullptr;

	std::string msg;
	LPVOID		msgErrorBuffer;

	int errorCode = WSAGetLastError();
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

	msg = reinterpret_cast<LPSTR>(&msgErrorBuffer);
	LocalFree(msgErrorBuffer);

	return std::move(msg);
}

