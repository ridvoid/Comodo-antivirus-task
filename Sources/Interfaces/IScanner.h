#pragma once

#include "..\Common\Header.h"

namespace Test
{

	class IScanner
	{

		IScanner(const IScanner&) = delete;
		IScanner(IScanner&&) = delete;
		IScanner& operator = (const IScanner&) = delete;
		IScanner& operator = (IScanner&&) = delete;

	public:

		IScanner(void) = default;
		
		virtual ~IScanner(void) = default;

		virtual IScanner& Load(void) = 0;

		virtual std::vector<BYTE> Scan(LPCBYTE,
			std::size_t) = 0;

		virtual std::vector<BYTE> Scan(const std::wstring&) = 0;

		template<typename T>
		static std::unique_ptr<IScanner> Create(void)
		{

			return std::unique_ptr<IScanner>(new T);

		}

	};

}