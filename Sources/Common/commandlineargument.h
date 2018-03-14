#pragma once


#include "..\..\Sources\Common\Exceptions.h"

namespace Test
{

	class CommandLineArgument
	{

		CommandLineArgument(void) = delete;
		CommandLineArgument(const CommandLineArgument&) = delete;
		CommandLineArgument(CommandLineArgument&&) = delete;
		CommandLineArgument& operator = (const CommandLineArgument&) = delete;
		CommandLineArgument& operator = (CommandLineArgument&&) = delete;
		~CommandLineArgument(void) = delete;

	public:

		static std::vector<std::wstring> GetCommandLines(void);

	};

}
