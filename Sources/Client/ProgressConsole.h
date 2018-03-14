#pragma once

#include "..\Interfaces\IProgress.h"

namespace Test
{

	class ProgressConsole : public IProgress
	{

		ProgressConsole(const ProgressConsole&) = delete;
		ProgressConsole(ProgressConsole&&) = delete;
		ProgressConsole& operator = (const ProgressConsole&) = delete;
		ProgressConsole& operator = (ProgressConsole&&) = delete;

	public:

		ProgressConsole(void) = default;

		virtual ~ProgressConsole(void) = default;

		IProgress& Show(const std::wstring&,
			BYTE) override;

	};

}
