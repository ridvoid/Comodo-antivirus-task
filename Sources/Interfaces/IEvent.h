#pragma once

#include "Wrap.h"
#include "Exceptions.h"

namespace Test
{

	class IEvent
	{

	protected:

		IEvent(const IEvent&) = delete;
		IEvent(IEvent&&) = delete;
		IEvent & operator = (const IEvent&) = delete;
		IEvent & operator = (IEvent&&) = delete;
		
		using Handle = std::unique_ptr<Wrap::Common::Handle>;

		Handle h{};

	public:

		explicit IEvent(HANDLE h = {}) : h(Wrap::Common::Handle::Create<Wrap::Common::Handle>(h)) { }

		explicit IEvent(Handle& h) : h(std::move(h)) { }

		virtual ~IEvent(void) = default;

		void IEvent::Set(void) const
		{

			if (!::SetEvent(*this->h))
				throw IEventException(L"Error SetEvent",
					GetLastError());

		}

		virtual void Reset(void) const = 0;

		DWORD Wait(DWORD dwWait = INFINITE) const
		{

			return this->h->Wait(dwWait);

		}

		operator HANDLE (void) const noexcept
		{

			return *this->h;

		}

	protected:

		template<typename T>
		static std::unique_ptr<IEvent> Create(LPSECURITY_ATTRIBUTES lpSecAttr,
			BOOL bManualReset,
			BOOL bInitialState,
			const std::wstring& wsName)
		{

			auto h = Wrap::Common::Handle::Create<Wrap::Common::Handle>(::CreateEvent(lpSecAttr,
				bManualReset,
				bInitialState,
				wsName.c_str()));
			if (!*h)
				throw IEventException(L"Error CreateEvent",
					GetLastError());

			return std::unique_ptr<IEvent>(new T(h));

		}

	};

}
