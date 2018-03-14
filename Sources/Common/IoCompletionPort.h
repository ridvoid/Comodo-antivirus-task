#pragma once

#include "Exceptions.h"
#include "Wrap.h"
#include "..\Interfaces\IWorker.h"

namespace Test
{

	class IoCompletionPort
	{

		IoCompletionPort(void) = default;
		IoCompletionPort(const IoCompletionPort&) = delete;
		IoCompletionPort(IoCompletionPort&&) = delete;
		IoCompletionPort & operator = (const IoCompletionPort&) = delete;
		IoCompletionPort & operator = (IoCompletionPort&&) = delete;

	public:

		struct Settings
		{

			HANDLE FileHandle{ INVALID_HANDLE_VALUE };
			HANDLE ExistingCompletionPort{};
			ULONG_PTR CompletionKey{};
			DWORD dwNumberOfConcurrentThreads{};

		};

	protected:

		Settings settings{};

		using Handle = std::unique_ptr<Wrap::Common::Handle>;

		Handle h{};

		std::list<std::thread> listThreads{};

		enum KeyExit : ULONG_PTR { Exit = ULONG_PTR(-1) };

		IoCompletionPort(const Settings&);

	public:
		
		virtual ~IoCompletionPort(void) noexcept;

		static std::unique_ptr<IoCompletionPort> Create(const Settings&);

	protected:

		IoCompletionPort& Create(void);

	public:

		IoCompletionPort& Start(void);

		IoCompletionPort& Add(ULONG_PTR);

		IoCompletionPort& Add(HANDLE,
			ULONG_PTR);

	private:

		void Receive(void) const noexcept;

		void Close(void) noexcept;

		void CheckKey(ULONG_PTR) const;

	};
}