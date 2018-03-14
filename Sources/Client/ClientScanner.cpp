
#include "ClientScanner.h"

namespace Test
{

	const std::wstring ClientScanner::wsTitle(L"Scanning");

	const std::list<std::wstring> ClientScanner::listExtensions
	{

		L".exe",
		L".dll",
		L".sys",
		L".drv",
		L".ocx",
		L".bat",
		L".bin",
		L".cmd",
		L".com",
		L".cpl",
		L".inf",
		L".pif",
		L".vb",
		L".vbe",
		L".vbs",
		L".vbscript",
		L".ws",
		L".wsf",
		L".dat"

	};

	BYTE ClientScanner::bCurrentPercent{};

	ClientScanner::ClientScanner(void) : dwNumberOfProcessors(SystemInfo::GetSystemInfo().dwNumberOfProcessors * Constants::Cpu::Multiplier) { }

	IScanner& ClientScanner::Load(void)
	{

		return this->CreateTasks().CreateThreadPool();

	}

	ClientScanner& ClientScanner::CreateTasks(void)
	{

		for (auto i = DWORD{}; i < this->dwNumberOfProcessors; ++i)
		{

			File::Settings settingsFile{};
			settingsFile.wsFileName = Constants::wsNamePipe;
			settingsFile.dwDesiredAccess = GENERIC_WRITE | GENERIC_READ;
			settingsFile.dwCreationDisposition = OPEN_EXISTING;

			this->vecTask.emplace_back(WorkerClientScanner::Create(AutoEvent::Create(),
				File::Create(settingsFile),
				this->vecResult,
				this->mutex));

		}

		return *this;

	}

	ClientScanner& ClientScanner::CreateThreadPool(void)
	{

		IoCompletionPort::Settings settings{};
		settings.dwNumberOfConcurrentThreads = this->dwNumberOfProcessors;

		(this->threadPool = IoCompletionPort::Create(settings))->Start();

		return *this;

	}

	std::vector<BYTE> ClientScanner::Scan(LPCBYTE,
		std::size_t)
	{

		throw ClientScannerException(L"ClientScanner::Scan",
			ERROR_NOT_SUPPORTED);

	}

	std::vector<BYTE> ClientScanner::Scan(const std::wstring& wsDir)
	{

		this->listFiles = Test::Directory::GetFiles(wsDir,
			ClientScanner::listExtensions,
			true);

		if (!this->listFiles.size())
			return{};

		this->sizeFullTask = this->listFiles.size();

		return (this->CreateEventHandles().CreateProgress().ScanFirstFiles().ScanNextFiles().ScanClose()).vecResult;

	}

	ClientScanner& ClientScanner::CreateEventHandles(void)
	{

		this->vecEventHandles = std::vector<HANDLE>(this->dwNumberOfProcessors);

		for (std::size_t i{}; i < this->vecEventHandles.size(); ++i)
			this->vecEventHandles[i] = *this->vecTask[i];

		return *this;

	}

	ClientScanner& ClientScanner::CreateProgress(void)
	{

		this->progress = IProgress::Create<ProgressConsole>();

		return *this;

	}

	ClientScanner& ClientScanner::ScanFirstFiles(void)
	{

		for (DWORD i{}; i < this->dwNumberOfProcessors && !this->listFiles.empty(); ++i)
			this->AddTaskToThreadPool(i);

		return *this;

	}

	ClientScanner& ClientScanner::ScanNextFiles(void)
	{

		while (!this->listFiles.empty() && this->dwCountBadTask != this->dwNumberOfProcessors)
			this->AddTaskToThreadPool(Test::Wrap::Common::Handle::Wait(this->vecEventHandles,
				FALSE));

		return *this;

	}

	ClientScanner& ClientScanner::ScanClose(void)
	{

		Test::Wrap::Common::Handle::Wait(this->vecEventHandles);

		return *this;

	}

	ClientScanner& ClientScanner::AddTaskToThreadPool(DWORD dwIndex)
	{

		std::unique_lock<std::mutex> lock(this->mutex);

		if (!this->vecTask[dwIndex]->IsWorked())
		{

			++this->dwCountBadTask;
			this->CheckBadScan();
			return *this;

		}

		this->vecTask[dwIndex]->Data() = Convert::ToBytes(this->listFiles.front());
		this->threadPool->Add(reinterpret_cast<ULONG_PTR>(this->vecTask[dwIndex].get()));
		this->listFiles.pop_front();

		auto bCurrentPercent = static_cast<BYTE>(((++this->sizeCountTask) * IProgress::Hundred / this->sizeFullTask));

		if (bCurrentPercent != ClientScanner::bCurrentPercent)
			this->progress->Show(ClientScanner::wsTitle,
				ClientScanner::bCurrentPercent = bCurrentPercent);
		
		return *this;

	}

	void ClientScanner::CheckBadScan(void) const
	{

		if (this->dwCountBadTask == this->dwNumberOfProcessors)
			throw ClientScannerException(L"Server is not avialible");

	}

}
