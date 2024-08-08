#pragma once

#include "pch.h"

class MyNetwork
{
private:
	SOCKET m_sock; // For server or client socket
		
public:
	virtual void Recv() const noexcept;
	virtual void Send() noexcept;
	virtual void Accept() noexcept;
	virtual void SetOption() noexcept;
	virtual void Run() noexcept;
};
