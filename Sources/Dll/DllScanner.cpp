
#include "DllScanner.h"

namespace Test
{

	const std::wstring DllScanner::wsSignatures(L"Signatures.txt");

	IScanner& DllScanner::Load(void)
	{

		std::wostringstream wos{};
		wos << Environment::GetCurDir() << L"\\" << DllScanner::wsSignatures;

		this->dbSignatures = Test::DbSignatures::Create(wos.str());
			
		this->dbSignatures->Load();

		return *this;

	}

	std::vector<BYTE> DllScanner::Scan(LPCBYTE lpcBuf,
		std::size_t sizeBuf)
	{

		return this->dbSignatures->Check(lpcBuf,
			sizeBuf);

	}

	
	std::vector<BYTE> DllScanner::Scan(const std::wstring& wsFile)
	{

		File::Settings settingsFile{};
		settingsFile.wsFileName = { wsFile };
		settingsFile.dwFlagsAndAttributes = File::GetAttributes(wsFile);
		auto file = File::Create(settingsFile);
		auto liSizeFile = file->GetSize();
		if (!liSizeFile.QuadPart)
			return{};

		MapFile::SettingsCreate settingsMap{};
		settingsMap.hFile = *file;
		auto map = MapFile::Create(settingsMap);

		map->ViewOfFile({});

		return this->dbSignatures->Check(*map,
			static_cast<std::size_t>(liSizeFile.QuadPart));

	}

}
