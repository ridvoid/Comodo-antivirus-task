
#include "CommandLineArgument.h"

namespace Test
{

	std::vector<std::wstring> CommandLineArgument::GetCommandLines(void)
	{

		auto nArgs{0};

		auto pszArglist = CommandLineToArgvW(GetCommandLineW(),
			&nArgs);
		if (!pszArglist)
			throw CommandLineArgumentException(L"Error CommandLineToArgvW",
				GetLastError());
	
		std::vector<std::wstring> vecReturn;
		for (auto i{0}; i < nArgs; i++)
			vecReturn.emplace_back(pszArglist[i]);

		LocalFree(pszArglist);

		return vecReturn;

	}
}
