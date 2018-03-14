#pragma once

#include "..\Interfaces\IFile.h"

namespace Test
{

	class File : public IFile
	{

		File(void) = default;
		File(const File&) = delete;
		File(File&&) = delete;
		File& operator = (const File&) = delete;
		File& operator = (File&&) = delete;

	public:

		struct Settings
		{

			std::wstring wsFileName{};
			DWORD dwDesiredAccess{ GENERIC_READ };
			DWORD dwShareMode{ FILE_SHARE_READ };
			LPSECURITY_ATTRIBUTES lpSecurityAttributes{};
			DWORD dwCreationDisposition{ OPEN_EXISTING };
			DWORD dwFlagsAndAttributes{ FILE_ATTRIBUTE_NORMAL };
			HANDLE hTemplateFile{};

		};

	private:

		Settings settings{};

	public:

		explicit File(const Settings&);

		virtual ~File(void) = default;

		static std::unique_ptr<IFile> Create(const Settings&);
		
	private:

		IFile& Create(void) override;

		IFile& Connect(LPOVERLAPPED = {}) const override;

		IFile& Disconnect(void) const override;

	public:

		LARGE_INTEGER GetSize(void) const override;
		
		static DWORD GetAttributes(const std::wstring&);

		static std::wstring GetExtension(const std::wstring&);

	};

}
