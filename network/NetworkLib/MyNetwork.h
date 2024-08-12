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
	private:
		bool InitWinSock() const noexcept;
		bool DelWinSock() const noexcept;

		void operator=(const MyNetwork&) = delete;
		void operator=(MyNetwork&&)		 = delete;
		MyNetwork(const MyNetwork&)		 = delete;
		MyNetwork(MyNetwork&&)			 = delete;
		
	protected:
		MyNetwork();

	public:
		virtual ~MyNetwork();

		bool IsError() const noexcept;
		bool IsError(int errorCode) const noexcept;
		std::string GetErrorMsg(int errorCode) const noexcept;
	};
}
