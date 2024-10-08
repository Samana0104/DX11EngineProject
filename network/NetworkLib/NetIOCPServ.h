#pragma once

#include "pch.h"
#include "Network.h"

namespace HBSoft
{
    const uint8_t MAX_WORKERS = 6;

    class NetIOCPServ : public Network
    {
    private:
        sockaddr_in    m_servAddr;
        SOCKET         m_servSock;
        HANDLE         m_iocpHandle;
        SessionManager m_sessionManager;

        std::thread m_workers[MAX_WORKERS];
        std::mutex  m_beginMutex;
        ConditionV  m_beginCondition;

        std::atomic<bool> m_isRunning = false;

    private:
        void operator=(const NetIOCPServ&) = delete;
        void operator=(NetIOCPServ&&)      = delete;
        NetIOCPServ(const NetIOCPServ&)    = delete;
        NetIOCPServ(NetIOCPServ&&)         = delete;

        bool ListenSock() noexcept;
        bool AcceptSock() noexcept;
        bool CreateSock(const PORT servPort) noexcept;
        bool BindSock() noexcept;

        void Disconnet(const Session& session) noexcept;

        void WorkerMain(NetIOCPServ& iocpServer);

    public:
        NetIOCPServ(const PORT servPort);
        virtual ~NetIOCPServ();

        void Run();
    };
}  // namespace HBSoft
