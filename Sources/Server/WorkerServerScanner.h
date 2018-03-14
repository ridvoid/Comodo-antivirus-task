#pragma once

#include "..\Common\File.h"
#include "..\Interfaces\IWorker.h"
#include "..\Interfaces\IScanner.h"
#include "..\Common\NamedPipe.h"
#include "..\Common\Convert.h"

namespace Test
{

	class WorkerServerScanner : public IWorker
	{

		WorkerServerScanner(void) = default;
		WorkerServerScanner(const WorkerServerScanner&) = delete;
		WorkerServerScanner(WorkerServerScanner&&) = delete;
		WorkerServerScanner& operator = (const WorkerServerScanner&) = delete;
		WorkerServerScanner& operator = (WorkerServerScanner&&) = delete;

		IScanner* pIScanner{};

		using Pipe = std::unique_ptr<IFile>;
		Pipe pipe{};

		WorkerServerScanner(IScanner*,
			Pipe&);

		enum class Type : BYTE { Connect = 1, Read, Write };

		struct Overlapped
		{

			OVERLAPPED overrlapped{};

			Type type = { Type::Connect };

			std::vector<BYTE> vecBuf{};

			Overlapped(const OVERLAPPED& overrlapped = {},
				Type type = { Type::Connect },
				const std::vector<BYTE>& vecBuf = {}) : 
				overrlapped(overrlapped), type(type), vecBuf(vecBuf){ }

		};

		Overlapped overlapped{};

	public:

		virtual ~WorkerServerScanner(void) = default;

		static std::unique_ptr<WorkerServerScanner> Create(IScanner*,
			Pipe&);

		void Run(ULONG_PTR,
			LPOVERLAPPED,
			DWORD) override;

		operator HANDLE(void) const override;

		IWorker& SetErrCode(DWORD);
		
	private:

		std::vector<BYTE>& Data(void);

		WorkerServerScanner& Connect(void);

		WorkerServerScanner& Read(void);

		WorkerServerScanner& Write(void);

		WorkerServerScanner& Disconnect(void);

	};

}
