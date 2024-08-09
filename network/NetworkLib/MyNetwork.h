#pragma once

#include "pch.h"

namespace MyProject
{
	enum 
	class MyNetwork
	{
	private:
		SOCKET m_sock; // For server or client socket

	private:
		bool InitSock() noexcept;
		bool DelWinSock() noexcept;

	public:
		MyNetwork();
		MyNetwork();
		~MyNetwork();

		virtual void Recv() const;
		virtual void Send();
		virtual void Accept();
		virtual void Disconnet();
		virtual void Run();

		bool IsError() const noexcept;

		static std::string GetErrorMsg() noexcept;

		// 추후 구현 예정
		//template < class T >
		//static void SetSockOption(int level, int option, T value);
		//template < class T >
		//static void GetSockOption(int level, int option, T value);
	};
}
