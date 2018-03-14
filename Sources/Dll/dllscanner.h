#pragma once

#include "..\Interfaces\IScanner.h"
#include "..\Common\Exceptions.h"
#include "..\Common\File.h"
#include "..\Common\MapFile.h"
#include "..\Dll\DbSignatures.h"
#include "..\Common\Environment.h"

namespace Test
{

	class DllScanner : public IScanner
	{

		DllScanner(const DllScanner &) = delete;
		DllScanner(DllScanner&&) = delete;
		DllScanner& operator = (const DllScanner&) = delete;
		DllScanner& operator = (DllScanner&&) = delete;

		using DbSignatures = std::unique_ptr<IDbSignatures>;

		DbSignatures dbSignatures{};

		static const std::wstring wsSignatures;
		
	public:

		DllScanner(void) = default;

		virtual ~DllScanner(void) = default;

		IScanner& Load(void) override;

		std::vector<BYTE> Scan(LPCBYTE,
			std::size_t) override;

		std::vector<BYTE> Scan(const std::wstring&) override;

	};

}
