#include "pch.h"
#include "MyNetIOCPServ.h"
using namespace MyProject;

MyNetIOCPServ::MyNetIOCPServ(const PORT servPort)
{
    assert(CreateSock(servPort));
    assert(BindSock());
    assert(ListenSock());

    m_iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
    
    for (int i = 0; i < MAX_WORKERS; i++)
        m_workers[i] = std::thread(&MyNetIOCPServ::WorkerMain, this, std::ref(*this));

    m_isRunning = true;
}

MyNetIOCPServ::~MyNetIOCPServ()
{
    closesocket(m_servSock);
    m_isRunning = false;

    for (int i = 0; i < MAX_WORKERS; i++)
    {
        m_workers[i].join();
    }
}

void MyNetIOCPServ::WorkerMain(MyNetIOCPServ& iocpServer)
{
    {
        std::unique_lock<std::mutex> lock(m_beginMutex);
        m_beginCondition.wait(lock);
    }
    
    while (m_isRunning)
    {

    }
}

void MyNetIOCPServ::Run()
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

bool MyNetIOCPServ::BindSock() noexcept
{
    int errorCode;
    errorCode = bind(m_servSock, reinterpret_cast<sockaddr*>(&m_servAddr), sizeof(m_servAddr));
    return !IsError(errorCode);
}


void MyNetIOCPServ::Disconnet(Session& session) noexcept
{
}

bool MyNetIOCPServ::ListenSock() noexcept
{
    int errorCode;
    errorCode = listen(m_servSock, SOMAXCONN);
    
    return !IsError(errorCode);
}

bool MyNetIOCPServ::AcceptSock() noexcept
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

bool MyNetIOCPServ::CreateSock(const PORT servPort) noexcept
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

