
#include "ServerScanner.h"

namespace Test
{

	const std::wstring ServerScanner::wsDll(L"Dll.dll");
	
	const std::vector<std::string> ServerScanner::vecFuncs =
	{

		"LoadSignature",
		"ScanFile"

	};

	ServerScanner::ServerScanner(void) : dwNumberOfProcessors(SystemInfo::GetSystemInfo().dwNumberOfProcessors * Constants::Cpu::Multiplier){}

	ServerScanner::~ServerScanner(void)
	{

		this->poolWorkers = {};
		
		this->dll = {};

		this->listWorkers.clear();

	}

	ServerScanner& ServerScanner::Start(void)
	{

		return this->Load();

	}
	
	ServerScanner& ServerScanner::Load(void)
	{

		return static_cast<const ServerScanner&>(this->LoadDll().CreateThreadPool().CreateWorkers().Bind()).Start();

	}

	ServerScanner& ServerScanner::LoadDll(void)
	{

		std::wostringstream wos{};
		wos << Test::Environment::GetCurDir() << L"\\" << ServerScanner::wsDll;

		this->dll = Test::Dll::Load(wos.str());

		this->pfnLoad = reinterpret_cast<PfnLoad>(Test::Dll::GetFuncByName(this->dll,
			ServerScanner::vecFuncs[Index::LoadFunc]));

		this->pfnLoad();

		this->pfnScan = reinterpret_cast<PfnScan>(Test::Dll::GetFuncByName(this->dll,
			ServerScanner::vecFuncs[Index::ScanFunc]));

		return *this;

	}

	ServerScanner& ServerScanner::CreateThreadPool(void)
	{

		IoCompletionPort::Settings settings;
		settings.dwNumberOfConcurrentThreads = this->dwNumberOfProcessors;

		this->poolWorkers = IoCompletionPort::Create(settings);

		return *this;

	}

	ServerScanner& ServerScanner::CreateWorkers(void)
	{

		for (auto i = DWORD{}; i < this->dwNumberOfProcessors; ++i)
		{

			NamedPipe::Settings settings{};
			settings.wsName = Constants::wsNamePipe;
			settings.dwOpenMode = PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED;
			settings.dwPipeMode = PIPE_TYPE_BYTE | PIPE_WAIT;
			settings.nMaxInstances = this->dwNumberOfProcessors;

			this->listWorkers.emplace_back(WorkerServerScanner::Create(this,
				NamedPipe::Create(settings)));

		}

		return *this;

	}

	ServerScanner& ServerScanner::Bind(void)
	{

		for (const auto& i : this->listWorkers)
			this->poolWorkers->Add(*i,
				reinterpret_cast<ULONG_PTR>(i.get()));

		return *this;

	}

	ServerScanner& ServerScanner::Start(void) const
	{

		this->poolWorkers->Start();

		return *const_cast<ServerScanner*>(this);

	}

	std::vector<BYTE> ServerScanner::Scan(LPCBYTE,
		std::size_t)
	{

		throw ServerScannerException(L"ServerScanner::Scan",
			ERROR_NOT_SUPPORTED);

	}

	std::vector<BYTE> ServerScanner::Scan(const std::wstring& wsFile)
	{

		std::vector<BYTE> vecReturn{};

		try
		{

			vecReturn = this->pfnScan(wsFile);
			
		}
		catch (const WinApiException& ex)
		{

			vecReturn = Convert::ToBytes(ex.What());

		}
		catch (...)
		{

			vecReturn = Convert::ToBytes(L"Unhandled exception...");

		}

		return vecReturn;

	}

}
