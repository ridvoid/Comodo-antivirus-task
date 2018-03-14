
#include "ProgressConsole.h"

namespace Test
{

	IProgress& ProgressConsole::Show(const std::wstring& wsText,
		BYTE percent)
	{

		std::wcout << '\r' << wsText << L" " << percent << L" %";

		return *this;

	}
	
}
