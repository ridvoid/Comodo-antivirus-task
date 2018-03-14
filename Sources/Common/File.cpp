#pragma once
#include "File.h"

namespace Test
{

	File::File(const Settings& settings) : settings(settings){ } 
		
	std::unique_ptr<IFile> File::Create(const Settings& settings)
	{

		return IFile::Create<File, Settings>(settings);

	}

	IFile& File::Create(void)
	{

		IFile::h = Wrap::Common::Handle::Create<Wrap::Common::Handle>(CreateFile(this->settings.wsFileName.c_str(),
			this->settings.dwDesiredAccess,
			this->settings.dwShareMode,
			this->settings.lpSecurityAttributes,
			this->settings.dwCreationDisposition,
			this->settings.dwFlagsAndAttributes,
			nullptr));
		if (!*IFile::h)
			throw FileException(L"Error CreateFile",
				GetLastError());

		return *this;

	}

	IFile& File::Connect(LPOVERLAPPED) const
	{

		throw FileException(L"File::Connect",
			ERROR_NOT_SUPPORTED);

	}

	IFile& File::Disconnect(void) const
	{

		throw FileException(L"File::Disconnect",
			ERROR_NOT_SUPPORTED);

	}

	LARGE_INTEGER File::GetSize(void) const
	{

		LARGE_INTEGER liReturn{};
		if (!GetFileSizeEx(*IFile::h,
			&liReturn))
			throw FileException(L"Error GetFileSizeEx",
				GetLastError());

		return liReturn;

	}

	DWORD File::GetAttributes(const std::wstring& wsFile)
	{

		auto dwReturn = GetFileAttributes(wsFile.c_str());
		if (dwReturn == INVALID_FILE_ATTRIBUTES)
			throw FileException(L"Error GetFileAttributes",
				GetLastError());

		return dwReturn;

	}

	std::wstring File::GetExtension(const std::wstring& wsFile)
	{

		auto posExtension = wsFile.rfind('.');
		if (posExtension == std::wstring::npos)
			return std::wstring();

		return wsFile.substr(posExtension);

	}

}
