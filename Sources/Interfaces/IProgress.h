#pragma once

#include "..\Common\Header.h"

namespace Test
{

	class IProgress
	{

		IProgress(const IProgress&) = delete;
		IProgress(IProgress&&) = delete;
		IProgress& operator = (const IProgress&) = delete;
		IProgress& operator = (IProgress&&) = delete;
		
	public:

		IProgress(void) = default;

		virtual ~IProgress(void) = default;

		virtual IProgress& Show(const std::wstring&,
			BYTE) = 0;

		template<typename T>
		static std::unique_ptr<IProgress> Create(void)
		{

			return std::unique_ptr<IProgress>(new T);

		}

		static const std::size_t Hundred = { 100 };

	};

}
