#pragma once

#include "pch.h"

namespace MyProject
{
	enum class IPProtocol
	{
		TCP,
		UDP 
	};

	class MyNetwork
	{
	protected:
		IPProtocol m_netProt;
		
	private:
		bool InitSock() const noexcept;
		bool DelWinSock() const noexcept;

		void operator=(const MyNetwork&) = delete;
		void operator=(MyNetwork&&)		 = delete;
		MyNetwork(const MyNetwork&)		 = delete;
		MyNetwork(MyNetwork&&)			 = delete;
		
	protected:
		MyNetwork(IPProtocol netProt);

		virtual void RecvByTCP() = 0;
		virtual void RecvByUDP() = 0;

		virtual void SendByTCP() = 0;
		virtual void SendByUDP() = 0;

		virtual void BindSock() = 0;
		virtual void Disconnet() = 0;

	public:
		virtual ~MyNetwork();

		bool IsError() const noexcept;
		std::string GetErrorMsg() const noexcept;

		void RecvPacket();
		void SendPacket();
		virtual void Run() = 0;
		
		
		// 추후 구현 예정
		//template < class T >
		//static void SetSockOption(int level, int option, T value);
		//template < class T >
		//static void GetSockOption(int level, int option, T value);
	};
}
