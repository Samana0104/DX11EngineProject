#pragma once

#include "pch.h"

namespace HBSoft
{
	enum class IPProtocol
	{
		TCP,
		UDP 
	};

	class Network
	{
	private:
		bool InitWinSock() const noexcept;
		bool DelWinSock() const noexcept;

		void operator=(const Network&) = delete;
		void operator=(Network&&)		 = delete;
		Network(const Network&)		 = delete;
		Network(Network&&)			 = delete;
		
	protected:
		Network();

	public:
		virtual ~Network();

		bool IsError() const noexcept;
		bool IsError(int errorCode) const noexcept;
		std::string GetErrorMsg(int errorCode) const noexcept;
	};
}
