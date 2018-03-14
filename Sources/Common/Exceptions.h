//---------------------------------------------------------------------------

#pragma once
#include "..\Common\Header.h"

//---------------------------------------------------------------------------

namespace Test
{

	class WinApiException
	{

		WinApiException(void) = delete;
		
		std::wstring wsText{};
		DWORD dwErrCode{};

	public:

		explicit WinApiException(const std::wstring&,
			DWORD) noexcept;

		explicit WinApiException(const std::wstring&) noexcept;

		explicit WinApiException(DWORD) noexcept;

		virtual ~WinApiException(void) = default;

		virtual std::wstring What(void) const;

		DWORD GetErrCode(void) const noexcept;

	};

	class HandleException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class FileException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class MapFileException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class ConvertException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class IoCompletionPortException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class DirectoryException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class IEventException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};
	
	class AutoEventException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class ThreadPoolException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class CommandLineArgumentException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class ClientScannerException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class DllException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};
	
	class NamedPipeException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class IFileException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class DbSignaturesException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};
	

	class WorkerServerScannerException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class EnvironmentException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class ServerScannerException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

}
