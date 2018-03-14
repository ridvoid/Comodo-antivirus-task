// dllmain.cpp : Defines the entry point for the DLL application.


#include "..\..\..\Sources\Common\Header.h"
#include "..\..\..\Sources\Dll\DllScanner.h"
#include "..\..\..\Sources\Common\Convert.h"

namespace Dll
{

	using Scanner = std::unique_ptr<Test::IScanner>;

	Scanner scanner{};

}

void LoadSignature(void);

std::vector<BYTE> ScanMemory(LPCBYTE,
	std::size_t);

std::vector<BYTE> ScanFile(const std::wstring&);

BOOL APIENTRY DllMain(HMODULE,
	DWORD ul_reason_for_call,
	LPVOID)
{

	BOOL bReturn{};

	try
	{

		switch (ul_reason_for_call)
		{

		case DLL_PROCESS_ATTACH:
			
			Dll::scanner = Test::IScanner::Create<Test::DllScanner>();

		default:

			bReturn = TRUE;

		}

	}
	catch (const std::exception& ex)
	{

		MessageBoxA({},
			ex.what(),
			"Dll",
			{});

	}
	catch (...)
	{

		MessageBox({},
			L"Dll",
			L"Unhandled exception",
			{});

	}

	return TRUE;

}

void LoadSignature(void)
{

	Dll::scanner->Load();

}

std::vector<BYTE> ScanMemory(LPCBYTE lpcBuf,
	std::size_t sizeBuf)
{

	return Dll::scanner->Scan(lpcBuf,
		sizeBuf);

}

std::vector<BYTE> ScanFile(const std::wstring& wsFile)
{

	return Dll::scanner->Scan(wsFile);

}