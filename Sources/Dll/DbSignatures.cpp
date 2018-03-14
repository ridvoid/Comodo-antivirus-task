
#include "DbSignatures.h"


namespace Test
{

	const std::regex DbSignatures::regex("^([0-9A-Fa-f]{1,})\\.(\\{[0-9A-Fa-f]{8}\\-[0-9A-Fa-f]{4}\\-[0-9A-Fa-f]{4}\\-[0-9A-Fa-f]{4}\\-[0-9A-Fa-f]{12}\\})$");

	DbSignatures::DbSignatures(const std::wstring& wsFile) noexcept : wsFile(wsFile) { }
	
	std::unique_ptr<IDbSignatures> DbSignatures::Create(const std::wstring& wsFile)
	{

		return std::unique_ptr<IDbSignatures>(new DbSignatures(wsFile));

	}

	IDbSignatures& DbSignatures::Load(void)
	{

		return this->Open().LoadFromFile();

	}

	std::vector<BYTE> DbSignatures::Check(LPCBYTE lpcBuf,
		std::size_t sizeBuf)
	{

		if (!lpcBuf || !sizeBuf)
			throw DbSignaturesException(L"Check",
				ERROR_INVALID_PARAMETER);

		std::size_t i{};
		std::size_t size{};
		while (i < sizeBuf)
		{

			for (const auto& pair : this->mapSign)
			{

				size = pair.first.size();

				if (size > sizeBuf - i)
					continue;

				if (memcmp(lpcBuf + i,
					pair.first.data(),
					size))
					continue;

				return Convert::ToBytes(Convert::AnsiToUnicode(pair.second));

			}

			++i;

		}
		
		return Convert::ToBytes(Constants::wsNormal);

	}

	DbSignatures& DbSignatures::Open(void)
	{

		this->ifs = std::ifstream(this->wsFile);
		if (!ifs)
			throw DbSignaturesException(this->wsFile,
				ERROR_FILE_NOT_FOUND);

		return *this;

	}

	DbSignatures& DbSignatures::LoadFromFile(void)
	{

		std::string str;
		std::smatch match;

		while (!this->ifs.eof())
		{

			std::getline(this->ifs, 
				str);

			if (!std::regex_search(str, 
				match, 
				DbSignatures::regex))
				continue;

			if (match.size() != Index::Size)
				continue;

			this->mapSign.insert({ Convert::HexStringToBytes(match[Index::Bytes]),
				match[Index::Guid] });

		}

		return *this;

	}

}
