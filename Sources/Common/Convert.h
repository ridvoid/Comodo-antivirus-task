#pragma once
#include "Exceptions.h"

namespace Test
{

	class Convert
	{

		Convert(void) = delete;
		Convert(const Convert&) = delete;
		Convert(Convert&&) = delete;
		Convert& operator = (const Convert&) = delete;
		Convert& operator = (Convert&&) = delete;
		~Convert(void) = delete;

		enum { Two = 2, Hex = 16 };

	public:

		static std::vector<BYTE> HexStringToBytes(const std::string&);

		static std::vector<BYTE> ToBytes(const std::string&);

		static std::vector<BYTE> ToBytes(const std::wstring&);

		static std::wstring ToString(const std::vector<BYTE>&);

		static std::wstring ToLower(const std::wstring&);

		static std::wstring AnsiToUnicode(const std::string&);

	};

}

