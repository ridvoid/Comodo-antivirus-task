#pragma once

#include "..\Common\Header.h"

namespace Test
{

	class IServer
	{

		IServer(const IServer&) = delete;
		IServer(IServer&&) = delete;
		IServer& operator = (const IServer&) = delete;
		IServer& operator = (IServer&&) = delete;

	public:

		IServer(void) = default;
		
		virtual ~IServer(void) = default;

		virtual IServer& Start(void) = 0;

		template<typename T>
		static std::unique_ptr<IServer> Create(void)
		{

			return std::unique_ptr<IServer>(new T);

		}

	};

}