#pragma once
#include "Convert.h"

namespace Test
{

	std::vector<BYTE> Convert::HexStringToBytes(const std::string& strHex)
	{

		std::istringstream is(strHex.length() % Two ? "0" + strHex : strHex);

		std::vector<BYTE> vecReturn(is.str().length() / Two);

		auto it = vecReturn.begin();

		std::string strTmp(Two,
			{});

		while (!is.eof() && it != vecReturn.cend())
		{

			is.read(&strTmp[0], 
				strTmp.size());

			*it++ = static_cast<BYTE>(std::stoul(strTmp, 
				{}, 
				Hex));

		}
		
		return vecReturn;

	}

	std::vector<BYTE> Convert::ToBytes(const std::string& str)
	{

		return std::vector<BYTE>(str.cbegin(),
			str.cend());

	}

	std::vector<BYTE> Convert::ToBytes(const std::wstring& wstr)
	{

		std::vector<BYTE> vecReturn(wstr.length() * sizeof(wchar_t));

		memcpy_s(vecReturn.data(),
			vecReturn.size(),
			wstr.c_str(),
			vecReturn.size());

		return vecReturn;

	}

	std::wstring Convert::ToString(const std::vector<BYTE>& vecBuf)
	{

		std::wstring wsReturn(vecBuf.size() / sizeof(wchar_t) + 1,
			'\0');

		memcpy_s(&wsReturn[0],
			vecBuf.size(),
			vecBuf.data(),
			vecBuf.size());

		return wsReturn.c_str();

	}

	std::wstring Convert::ToLower(const std::wstring& ws)
	{

		auto wsReturn = std::wstring(ws.length(), 
			'\0');
		std::transform(ws.cbegin(),
			ws.cend(),
			wsReturn.begin(),
			[](wchar_t wch)
		{

			return static_cast<char>(std::tolower(wch));

		});
		
		return wsReturn;

	}

	std::wstring Convert::AnsiToUnicode(const std::string& str)
	{

		std::wstring wsReturn(str.size() + 1,
			'\0');

#pragma warning(push)
#pragma warning(disable : 4267)
		auto iRet = ::MultiByteToWideChar(CP_ACP,
			MB_PRECOMPOSED,
			str.c_str(),
			str.size(),
			&wsReturn[0],
			static_cast<int>(wsReturn.size()));
#pragma warning(pop)
		if (!iRet)
			throw ConvertException(L"Error MultiByteToWideChar",
				::GetLastError());

		return wsReturn.c_str();

	}

}

