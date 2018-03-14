
#include "Exceptions.h"


namespace Test
{

	WinApiException::WinApiException(const std::wstring& wsText,
		DWORD dwErrCode) noexcept : wsText(wsText), dwErrCode(dwErrCode) { }

	WinApiException::WinApiException(const std::wstring& wsText) noexcept : WinApiException(wsText, {}) { }

	WinApiException::WinApiException(DWORD dwCode) noexcept : WinApiException({}, dwCode) { }

	std::wstring WinApiException::What(void) const
	{

		if (!this->dwErrCode)
			return this->wsText;

		LPVOID lpMsgBuf{};

		std::wostringstream wos{};
		wos << this->wsText << std::endl;

		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			nullptr,
			this->dwErrCode,
			MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
			reinterpret_cast<LPWSTR>(&lpMsgBuf),
			0,
			nullptr))
		{

			wos << reinterpret_cast<LPCWSTR>(lpMsgBuf);

			LocalFree(lpMsgBuf);

		}

		wos << L"Error code " << this->dwErrCode << std::endl;

		return wos.str();

	}

	DWORD WinApiException::GetErrCode(void) const noexcept
	{

		return this->dwErrCode;

	}

}
