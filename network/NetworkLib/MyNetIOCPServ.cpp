#include "pch.h"
#include "MyNetIOCPServ.h"
using namespace MyProject;

MyNetIOCPServ::MyNetIOCPServ(const PORT servPort)
	: MyNetwork(IPProtocol::TCP)
{
    assert(CreateSock(servPort));
    assert(ListenSock());
}

MyNetIOCPServ::~MyNetIOCPServ()
{
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

void MyNetIOCPServ::RecvByTCP()
{
}

void MyNetIOCPServ::RecvByUDP()
{
}

void MyNetIOCPServ::SendByTCP()
{
}

void MyNetIOCPServ::SendByUDP()
{
}

void MyNetIOCPServ::BindSock()
{
    bind(m_servSock, reinterpret_cast<sockaddr*>(&m_servAddr), sizeof(m_servAddr));
    assert(IsError());
}

bool MyNetIOCPServ::ListenSock() noexcept
{
    listen(m_servSock, SOMAXCONN);
    
    return IsError();
}

bool MyNetIOCPServ::AcceptSock() noexcept
{
    return IsError();
}

bool MyNetIOCPServ::CreateSock(const PORT servPort) noexcept
{
	m_servSock = socket(AF_INET, SOCK_STREAM, 0);
    u_long iNonSocket = TRUE;
    int iMode = ioctlsocket(m_servSock, FIONBIO, &iNonSocket);

    ZeroMemory(&m_servAddr, sizeof(m_servAddr));
    {
        m_servAddr.sin_addr.s_addr = INADDR_ANY;
        m_servAddr.sin_port = htons(servPort);
        m_servAddr.sin_family = AF_INET;
    }

    return IsError();
}

void MyNetIOCPServ::Disconnet()
{
}

