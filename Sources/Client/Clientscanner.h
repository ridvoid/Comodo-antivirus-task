#pragma once

#include "..\Interfaces\IScanner.h"
#include "..\..\Sources\Common\Exceptions.h"
#include "..\..\Sources\Common\IoCompletionPort.h"
#include "..\..\Sources\Common\SystemInfo.h"
#include "..\..\Sources\Common\Directory.h"
#include "..\..\Sources\Common\AutoEvent.h"
#include "..\..\Sources\Common\File.h"
#include "WorkerClientScanner.h"
#include "ProgressConsole.h"

namespace Test
{

	class ClientScanner : public IScanner
	{

		ClientScanner(const ClientScanner&) = delete;
		ClientScanner(ClientScanner&&) = delete;
		ClientScanner& operator = (const ClientScanner&) = delete;
		ClientScanner& operator = (ClientScanner&&) = delete;
		
		using Task = std::unique_ptr<IWorker>;
		std::vector<Task> vecTask = {};

		using ThreadPool = std::unique_ptr<IoCompletionPort>;
		ThreadPool threadPool{};

		DWORD dwNumberOfProcessors{};

		std::vector<HANDLE> vecEventHandles{};

		std::list<std::wstring> listFiles{};

		std::mutex mutex{};

		DWORD dwCountBadTask{};

		std::size_t sizeCountTask{}, sizeFullTask{};

		using Progress = std::unique_ptr<IProgress>;
		Progress progress{};

		static const std::wstring wsTitle;

		static const std::list<std::wstring> listExtensions;
		
		std::vector<BYTE> vecResult{};

		static BYTE bCurrentPercent;

	public:

		ClientScanner(void);

		virtual ~ClientScanner(void) = default;

		IScanner& Load(void) override;

		std::vector<BYTE> Scan(LPCBYTE,
			std::size_t) override;

		std::vector<BYTE> Scan(const std::wstring&);

	private:

		ClientScanner& CreateTasks(void);

		ClientScanner& CreateThreadPool(void);

		ClientScanner& CreateEventHandles(void);

		ClientScanner& CreateProgress(void);

		ClientScanner& ScanFirstFiles(void);

		ClientScanner& ScanNextFiles(void);

		ClientScanner& ScanClose(void);

		ClientScanner& AddTaskToThreadPool(DWORD);

		void CheckBadScan(void) const;

	};

}
