#pragma once
#include "..\Interfaces\IDbSignatures.h"
#include "..\Common\Convert.h"

namespace Test
{

	class DbSignatures : public IDbSignatures
	{

		DbSignatures(void) = delete;
		DbSignatures(const DbSignatures&) = delete;
		DbSignatures(DbSignatures&&) = delete;
		DbSignatures& operator = (const DbSignatures&) = delete;
		DbSignatures& operator = (DbSignatures&&) = delete;

		std::wstring wsFile{};

		enum Index : std::size_t { First, Bytes, Guid, Size };

		std::map<std::vector<BYTE>, std::string> mapSign{};

		static const std::regex regex;

		std::ifstream ifs{};

		explicit DbSignatures(const std::wstring& wsFile) noexcept;

	public:
		
		virtual ~DbSignatures(void) = default;

		static std::unique_ptr<IDbSignatures> Create(const std::wstring&);

		IDbSignatures& Load(void) override;

		std::vector<BYTE> Check(LPCBYTE,
			std::size_t) override;
		
	private:

		DbSignatures& Open(void);

		DbSignatures& LoadFromFile(void);

	};

}