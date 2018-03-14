
#include "SystemInfo.h"

namespace Test
{

	SYSTEM_INFO SystemInfo::GetSystemInfo(void)
	{

		SYSTEM_INFO si{};

		::GetSystemInfo(&si);

		return si;

	}

}
