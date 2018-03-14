#pragma once

#include "..\Common\Wrap.h"


namespace Test
{

	class Dll
	{

		Dll(void) = delete;
		Dll(const Dll&) = delete;
		Dll(Dll&&) = delete;
		Dll& operator = (const Dll&) = delete;
		Dll& operator = (Dll&&) = delete;
		~Dll(void) = delete;

	public:

		static std::unique_ptr<Wrap::Common::Handle> Load(const std::wstring&);

		static LPVOID GetFuncByName(const std::unique_ptr<Wrap::Common::Handle>&,
			const std::string&);

	};

}
