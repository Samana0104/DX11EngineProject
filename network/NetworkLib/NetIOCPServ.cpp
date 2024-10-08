#include "pch.h"
#include "NetIOCPServ.h"
using namespace HBSoft;

NetIOCPServ::NetIOCPServ(const PORT servPort)
{
    assert(CreateSock(servPort));
    assert(BindSock());
    assert(ListenSock());

    m_iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
    
    for (int i = 0; i < MAX_WORKERS; i++)
        m_workers[i] = std::thread(&NetIOCPServ::WorkerMain, this, std::ref(*this));

    m_isRunning = true;
}

NetIOCPServ::~NetIOCPServ()
{
    closesocket(m_servSock);
    m_isRunning = false;

    for (int i = 0; i < MAX_WORKERS; i++)
    {
        m_workers[i].join();
    }
}

void NetIOCPServ::WorkerMain(NetIOCPServ& iocpServer)
{
    {
        std::unique_lock<std::mutex> lock(m_beginMutex);
        m_beginCondition.wait(lock);
    }
    
    while (m_isRunning)
    {

    }
}

void NetIOCPServ::Run()
{
    while(true)
    {
        if (!AcceptSock())
        {
            break;
        }        
        //if (PacketProcess() == false)
        //{
        //    break;
        //}
        //CheckConnected();
    }
}

bool NetIOCPServ::BindSock() noexcept
{
    int errorCode;
    errorCode = bind(m_servSock, reinterpret_cast<sockaddr*>(&m_servAddr), sizeof(m_servAddr));
    return !IsError(errorCode);
}


void NetIOCPServ::Disconnet(Session& session) noexcept
{
}

bool NetIOCPServ::ListenSock() noexcept
{
    int errorCode;
    errorCode = listen(m_servSock, SOMAXCONN);
    
    return !IsError(errorCode);
}

bool NetIOCPServ::AcceptSock() noexcept
{
    sockaddr_in addr;
    int addrlen = sizeof(addr);
    SOCKET clientSock = accept(m_servSock, reinterpret_cast<sockaddr*>(&addr), &addrlen);
    if (clientSock == INVALID_SOCKET)
    {
        if (IsError())
            return false;
    }
    else
    {
        AddSession(clientSock, addr);
    }
    return true;
}

bool NetIOCPServ::CreateSock(const PORT servPort) noexcept
{
    u_long nonBlockSock = TRUE;
    int errorCode;

	m_servSock = socket(AF_INET, SOCK_STREAM, 0);

    if (m_servSock == INVALID_SOCKET)
        return false;

    errorCode = ioctlsocket(m_servSock, FIONBIO, &nonBlockSock);
    
    if (IsError(errorCode))
        return false;
    
    ZeroMemory(&m_servAddr, sizeof(m_servAddr));
    {
        m_servAddr.sin_addr.s_addr = INADDR_ANY;
        m_servAddr.sin_port = htons(servPort);
        m_servAddr.sin_family = AF_INET;
    }

    return true;
}

