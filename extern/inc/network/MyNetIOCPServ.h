#pragma once

#include "pch.h"
#include "MyNetwork.h"
namespace MyProject
{
	const uint8_t MAX_WORKERS = 6;

	class MyNetIOCPServ : public MyNetwork
	{
	private:
		sockaddr_in m_servAddr;
		SOCKET		m_servSock; // For server or client socket
		IOCPSession m_sessions;
		HANDLE		m_iocpHandle;

		std::thread m_workers[MAX_WORKERS];
		std::mutex  m_beginMutex;
		ConditionV  m_beginCondition;

		bool		m_isRunning = false;
		
	private:
		void operator=(const MyNetIOCPServ&) = delete;
		void operator=(MyNetIOCPServ&&)		 = delete;
		MyNetIOCPServ(const MyNetIOCPServ&)	 = delete;
		MyNetIOCPServ(MyNetIOCPServ&&)		 = delete;

		bool ListenSock() noexcept;
		bool AcceptSock() noexcept;
		bool CreateSock(const PORT servPort) noexcept;
		bool BindSock() noexcept;
		
		void WorkerMain(MyNetIOCPServ& iocpServer);

	protected:
		void Recv() noexcept;
		void Send() noexcept;

		void Disconnet(Session& session) noexcept;

	public:
		MyNetIOCPServ(const PORT servPort);
		virtual ~MyNetIOCPServ();

		void Run();
	};
}

