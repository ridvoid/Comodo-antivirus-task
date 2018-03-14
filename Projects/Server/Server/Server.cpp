// Server.cpp : Defines the entry point for the console application.
//

#include "..\..\..\Sources\Server\ServerScanner.h"

int main()
{

	auto iReturn{ -1 };

	using Server = std::unique_ptr<Test::IServer>;
	Server server{};

	try
	{

		server = Test::IServer::Create<Test::ServerScanner>();

		server->Start();

		std::wcout << L"Press enter to exit..." << std::endl;

		std::wcin.get();

		iReturn = {};

	}
	catch (const Test::WinApiException& ex)
	{

		std::wcout << ex.What() << std::endl;

		iReturn = static_cast<int>(ex.GetErrCode() ? ex.GetErrCode() : -1);

	}
	catch (const std::exception& ex)
	{

		std::cout << ex.what() << std::endl;

	}
	catch (...)
	{

		std::wcout << L"Unhandled exception..." << std::endl;

	}

	return iReturn;

}

