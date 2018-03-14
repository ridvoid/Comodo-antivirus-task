#pragma once

#include "..\..\Sources\Common\AutoEvent.h"
#include "..\..\Sources\Common\AutoSetEvent.h"
#include "..\..\Sources\Common\File.h"
#include "..\Interfaces\IWorker.h"
#include "..\..\Sources\Common\Convert.h"
#include "..\Interfaces\IScanner.h"

namespace Test
{

	class WorkerClientScanner : public IWorker
	{

		WorkerClientScanner(void) = default;
		WorkerClientScanner(const WorkerClientScanner&) = delete;
		WorkerClientScanner(WorkerClientScanner&&) = delete;
		WorkerClientScanner& operator = (const WorkerClientScanner&) = delete;
		WorkerClientScanner& operator = (WorkerClientScanner&&) = delete;

		using Event = std::unique_ptr<IEvent>;
		Event event{};

		using Pipe = std::unique_ptr<IFile>;
		Pipe pipe{};

		std::vector<BYTE> vecData{};

		IScanner* pIScanner{};

		std::mutex& mutex;

		std::vector<BYTE>& vecResult;

		explicit WorkerClientScanner(Event&,
			Pipe&,
			std::vector<BYTE>&,
			std::mutex&);

	public:

		virtual ~WorkerClientScanner(void) = default;

		static std::unique_ptr<IWorker> Create(Event&,
			Pipe&,
			std::vector<BYTE>&,
			std::mutex&);

		void Run(ULONG_PTR,
			LPOVERLAPPED,
			DWORD) override;
		
		operator HANDLE(void) const noexcept override;

		std::vector<BYTE>& Data(void) noexcept override;

	};

}