#pragma once

#include "pch.h"
#include "MyNetwork.h"

namespace MyProject
{
	class MyNetIOCPServ : public MyNetwork
	{
	private:
		sockaddr_in m_servAddr;
		SOCKET		m_servSock; // For server or client socket

	private:
		void operator=(const MyNetIOCPServ&) = delete;
		void operator=(MyNetIOCPServ&&)		 = delete;
		MyNetIOCPServ(const MyNetIOCPServ&)	 = delete;
		MyNetIOCPServ(MyNetIOCPServ&&)		 = delete;

		bool ListenSock() noexcept;
		bool AcceptSock() noexcept;
		bool CreateSock(const PORT servPort) noexcept;

	protected:
		virtual void RecvByTCP() override;
		virtual void RecvByUDP() override;

		virtual void SendByTCP() override;
		virtual void SendByUDP() override;

		virtual void BindSock() override;
		virtual void Disconnet() override;

	public:
		MyNetIOCPServ(const PORT servPort);
		virtual ~MyNetIOCPServ();

		virtual void Run() override;
	};
}

