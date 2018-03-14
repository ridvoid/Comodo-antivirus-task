//---------------------------------------------------------------------------

#pragma once

#include "Exceptions.h"

//---------------------------------------------------------------------------

namespace Test
{

	namespace Wrap
	{

		namespace Common
		{

			class Handle
			{

				Handle(const Handle&) = delete;
				Handle(Handle&&) = delete;
				Handle& operator = (const Handle&) = delete;
				Handle& operator = (Handle&&) = delete;

			protected:

				HANDLE h{};

			public:
				
				explicit Handle(HANDLE = {}) noexcept;

				virtual ~Handle(void) noexcept;

				virtual operator HANDLE (void) const noexcept;

				bool operator ! (void) const noexcept;

				DWORD Wait(DWORD = { INFINITE }) const;

				template<typename T>
				static std::unique_ptr<Handle> Create(HANDLE h)
				{

					return std::unique_ptr<Handle>(new T(h));

				}

				static DWORD Wait(const std::vector<HANDLE>&,
					BOOL = { TRUE },
					DWORD = { INFINITE });

				static DWORD Wait(HANDLE,
					DWORD = { INFINITE });

			};

		}

		namespace FindFile
		{

			class Handle : public Common::Handle
			{

				Handle(const Handle&) = delete;
				Handle(Handle&&) = delete;
				Handle& operator = (const Handle&) = delete;
				Handle& operator = (Handle&&) = delete;

			public:

				using Common::Handle::Handle;
			
				virtual ~Handle(void) noexcept;

			};

		}

		namespace Dll
		{

			class Handle : protected Common::Handle
			{

				Handle(const Handle&) = delete;
				Handle(Handle&&) = delete;
				Handle& operator = (const Handle&) = delete;
				Handle& operator = (Handle&&) = delete;

			public:

				explicit Handle(HMODULE = {}) noexcept;

				virtual ~Handle(void) noexcept;

				Common::Handle::operator!;

				Common::Handle::operator HANDLE;
				
				static std::unique_ptr<Wrap::Common::Handle> Create(HMODULE);
			

			};

		}
		
	}

}

