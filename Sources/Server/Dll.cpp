
#include "Dll.h"

namespace Test
{

	std::unique_ptr<Wrap::Common::Handle> Dll::Load(const std::wstring& wsPath)
	{
		
		auto uptrReturn = Wrap::Dll::Handle::Create(LoadLibrary(wsPath.c_str()));
		if (!*uptrReturn)
			throw DllException(L"Error LoadLibrary",
				GetLastError());

		return uptrReturn;

	}

	LPVOID Dll::GetFuncByName(const std::unique_ptr<Wrap::Common::Handle>& h,
		const std::string& strFuncName)
	{

		auto ptr = GetProcAddress(static_cast<HMODULE>(h->operator HANDLE()),
			strFuncName.c_str());
		if(!ptr)
			throw DllException(L"Error GetProcAddress",
				GetLastError());

		return ptr;

	}

}
