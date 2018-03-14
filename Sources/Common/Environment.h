#pragma once


#include "Exceptions.h"

namespace Test
{

	class Environment
	{

		Environment(void) = delete;
		Environment(const Environment&) = delete;
		Environment(Environment&&) = delete;
		Environment& operator = (const Environment&) = delete;
		Environment& operator = (Environment&&) = delete;
		~Environment(void) = delete;

		static const std::size_t sizeMaxPathLen = 32767;

	public:

		static std::wstring GetCurDir(void);

	};

}
