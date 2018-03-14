// Client.cpp : Defines the entry point for the console application.
//


#include "..\..\..\Sources\Common\CommandLineArgument.h"
#include "..\..\..\Sources\Client\ClientScanner.h"
#include "..\..\..\Sources\Common\Environment.h"

namespace Client
{

	enum Args : std::size_t { Dir = 1, Count };

	const std::wstring wsReport(L"Client.log");

	void Help(void);

	void Show(const std::wstring&);

	void Save(const std::vector<BYTE>&);

}

int main()
{

	auto iReturn = -1;

	try
	{

		auto vecArgs = Test::CommandLineArgument::GetCommandLines();
		if (vecArgs.size() != Client::Args::Count)
			throw Test::CommandLineArgumentException(ERROR_INVALID_PARAMETER);

		Client::Save(Test::IScanner::Create<Test::ClientScanner>()->Load().Scan(vecArgs[Client::Args::Dir]));

		iReturn = {};

		Client::Show(L"Done");

	}
	catch (const Test::CommandLineArgumentException& ex)
	{

		Client::Help();

		iReturn = static_cast<int>(ex.GetErrCode() ? ex.GetErrCode() : -1);

	}
	catch (const Test::WinApiException& ex)
	{

		Client::Show(ex.What());

		iReturn = static_cast<int>(ex.GetErrCode() ? ex.GetErrCode() : -1);

	}
	catch (const std::exception& ex)
	{

		std::cout << ex.what() << std::endl;

	}
	catch (...)
	{

		Client::Show(L"Unhandled exception...");

	}

	return iReturn;

}

void Client::Help(void)
{

	std::wcout << L"Invalid arguments" << std::endl;
	std::wcout << L"Example: Client.exe C:\\Windows" << std::endl;

}

void Client::Show(const std::wstring& wsText)
{

	std::wcout << std::endl << wsText << std::endl;

}

void Client::Save(const std::vector<BYTE>& vecBuf)
{

	std::wostringstream wos{};
	wos << Test::Environment::GetCurDir() << L"\\" << Client::wsReport;

	Test::File::Settings settings{};
	settings.wsFileName = wos.str();
	settings.dwDesiredAccess = GENERIC_WRITE;
	settings.dwCreationDisposition = CREATE_ALWAYS;
	
	Test::File::Create(settings)->Write(vecBuf);
	
}