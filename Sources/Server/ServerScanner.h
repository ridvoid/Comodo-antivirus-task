#pragma once

#include "..\Interfaces\IServer.h"
#include "..\Common\IoCompletionPort.h"
#include "..\Interfaces\IScanner.h"
#include "..\Common\SystemInfo.h"
#include "WorkerServerScanner.h"
#include "Dll.h"
#include "..\Common\Environment.h"


namespace Test
{

	class ServerScanner : public IServer, IScanner
	{

		ServerScanner(const ServerScanner&) = delete;
		ServerScanner(ServerScanner&&) = delete;
		ServerScanner& operator = (const ServerScanner&) = delete;
		ServerScanner& operator = (ServerScanner&&) = delete;
		
		using PoolWorkers = std::unique_ptr<IoCompletionPort>;
		PoolWorkers poolWorkers{};
		
		using Dll = std::unique_ptr<Wrap::Common::Handle>;
		Dll dll{};

		static const std::wstring wsDll;
		static const std::vector<std::string> vecFuncs;

		enum Index : std::size_t { LoadFunc, ScanFunc };

		using PfnLoad = void(*)(void);
		PfnLoad pfnLoad{};

		using PfnScan = std::vector<BYTE>(*)(const std::wstring&);
		PfnScan pfnScan{};

		using Worker = std::unique_ptr<IWorker>;
		std::list<Worker> listWorkers{};

		DWORD dwNumberOfProcessors{};

	public:

		ServerScanner(void);

		virtual ~ServerScanner(void);

		ServerScanner& Start(void) override;

	private:

		ServerScanner& Load(void) override;

		ServerScanner& LoadDll(void);

		ServerScanner& CreateThreadPool(void);

		ServerScanner& CreateWorkers(void);

		ServerScanner& Bind(void);

		ServerScanner& Start(void)const;

		std::vector<BYTE> Scan(LPCBYTE,
			std::size_t) override;

		std::vector<BYTE> Scan(const std::wstring&) override;
		
	};

}
