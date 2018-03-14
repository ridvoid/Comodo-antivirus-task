#pragma once
#include "..\Common\Header.h"

namespace Test
{

	class SystemInfo
	{

		SystemInfo(void) = delete;
		SystemInfo(const SystemInfo&) = delete;
		SystemInfo(SystemInfo&&) = delete;
		SystemInfo& operator = (const SystemInfo&) = delete;
		SystemInfo& operator = (SystemInfo&&) = delete;
		~SystemInfo(void) = delete;

	public:

		static SYSTEM_INFO GetSystemInfo(void);

	};

}