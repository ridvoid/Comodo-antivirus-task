#include "Wrap.h"

namespace Test
{

	namespace Wrap
	{

		namespace Common
		{

			Handle::Handle(HANDLE h) noexcept : h(h) { }

			Handle::~Handle(void) noexcept
			{

				if (this->h)
					CloseHandle(this->h);

			}

			Handle::operator HANDLE(void) const noexcept
			{

				return this->h;

			}

			bool Handle::operator !(void) const noexcept
			{

				return this->h == nullptr || this->h == INVALID_HANDLE_VALUE;

			}

			DWORD Handle::Wait(DWORD dwPeriod) const
			{

				return Handle::Wait(this->h,
					dwPeriod);

			}

			DWORD Handle::Wait(const std::vector<HANDLE>& vecHandles,
				BOOL bWaitAll,
				DWORD dwPeriod)
			{

				auto dwReturn = WaitForMultipleObjects(static_cast<DWORD>(vecHandles.size()),
					vecHandles.data(),
					bWaitAll,
					dwPeriod);
				if (dwReturn == WAIT_FAILED)
				{

					auto dwErrCode = GetLastError();
					throw HandleException(L"Error WaitForMultipleObjects",
						dwErrCode);

				}

				return dwReturn;

			}

			DWORD Handle::Wait(HANDLE h,
				DWORD dwPeriod)
			{

				auto dwReturn = WaitForSingleObject(h,
					dwPeriod);
				if (dwReturn == WAIT_FAILED)
				{

					auto dwErrCode = GetLastError();
					throw HandleException(L"Error WaitForSingleObject",
						dwErrCode);

				}

				return dwReturn;

			}

		}

		namespace FindFile
		{

			Handle::~Handle(void) noexcept
			{

				if (Common::Handle::h && this->h != INVALID_HANDLE_VALUE)
					FindClose(Common::Handle::h);

				Common::Handle::h = nullptr;

			}

		}

		namespace Dll
		{

			Handle::Handle(HMODULE h) noexcept : Common::Handle(h) { }

			Handle::~Handle(void) noexcept
			{

				if (Common::Handle::h)
					FreeLibrary(reinterpret_cast<HMODULE>(Common::Handle::h));

				Common::Handle::h = nullptr;

			}

			std::unique_ptr<Wrap::Common::Handle> Handle::Create(HMODULE h)
			{

				return std::unique_ptr<Wrap::Common::Handle>(new Handle(h));

			}

		}

	}

}


