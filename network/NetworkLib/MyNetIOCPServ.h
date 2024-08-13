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
		SOCKET		m_servSock; 
		HANDLE		m_iocpHandle;
		MySessionManager m_sessionManager;

		std::thread m_workers[MAX_WORKERS];
		std::mutex  m_beginMutex;
		ConditionV  m_beginCondition;

		std::atomic<bool> m_isRunning = false;
		
	private:
		void operator=(const MyNetIOCPServ&) = delete;
		void operator=(MyNetIOCPServ&&)		 = delete;
		MyNetIOCPServ(const MyNetIOCPServ&)	 = delete;
		MyNetIOCPServ(MyNetIOCPServ&&)		 = delete;

		bool ListenSock() noexcept;
		bool AcceptSock() noexcept;
		bool CreateSock(const PORT servPort) noexcept;
		bool BindSock() noexcept;
			
		void Disconnet(const Session& session) noexcept;

		void WorkerMain(MyNetIOCPServ& iocpServer);

	public:
		MyNetIOCPServ(const PORT servPort);
		virtual ~MyNetIOCPServ();

		void Run();
	};
}

