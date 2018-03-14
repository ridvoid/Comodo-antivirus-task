
#include "Environment.h"

namespace Test
{

	std::wstring Environment::GetCurDir(void)
	{

		std::wstring wsReturn(Environment::sizeMaxPathLen,
			{});

		auto dwResult = GetModuleFileName({},
			&wsReturn[0],
			static_cast<DWORD>(wsReturn.size()));
		if (!dwResult)
			throw EnvironmentException(L"Error GetModuleFileName",
				GetLastError());

		wsReturn.resize(dwResult);

		auto sizePos = wsReturn.rfind('\\');
		if(sizePos == std::wstring::npos)
			throw EnvironmentException(L"Error Environment::GetCurDir",
				ERROR_INVALID_PARAMETER);

		return wsReturn.substr({},
			sizePos);

	}



}
