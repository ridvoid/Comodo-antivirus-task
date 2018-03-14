#pragma once
#include "Directory.h"

namespace Test
{

	std::list<std::wstring> Directory::GetFiles(const std::wstring& wsPath,
		const std::list<std::wstring>& listMask,
		bool bRec)
	{

		Test::File::GetAttributes(wsPath);

		std::wostringstream wos{};
		if (wsPath[wsPath.length() - 1] == '\\')
			wos << wsPath.substr(0, 
				wsPath.length() - 1);
		else
			wos << wsPath;

		std::list<std::wstring> listReturn{};
		
		Directory::GetFiles(listReturn,
			wos.str(),
			listMask,
			bRec);

		return listReturn;

	}

	void Directory::GetFiles(std::list<std::wstring>& listReturn,
		const std::wstring& wsPath,
		const std::list<std::wstring>& listMask,
		bool bRec)
	{

		WIN32_FIND_DATA winFindData{};
		std::wostringstream wos{};
		wos << wsPath << L"\\*.*";

		auto h = Wrap::Common::Handle::Create<Wrap::FindFile::Handle>(FindFirstFile(wos.str().c_str(),
			&winFindData));
		if (!*h)
			throw DirectoryException(L"Error FindFirstFile",
				GetLastError());

		do
		{

			auto wsFile = std::wstring(winFindData.cFileName);
			if (wsFile == L"." || wsFile == L"..")
				continue;

			std::wostringstream wos{};
			wos << wsPath << L"\\" << wsFile;

			if ((winFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && bRec)
			{

				try
				{

					Directory::GetFiles(listReturn,
						wos.str(),
						listMask,
						bRec);

				}
				catch (WinApiException) { }

			}
			else if (!(winFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{

				if (listMask.empty())
				{

					listReturn.emplace_back(wos.str());
					continue;

				}

				if(Directory::IsEqualExtension(listMask,
					Convert::ToLower(File::GetExtension(wsFile))))
					listReturn.emplace_back(wos.str());

			}

		} while (FindNextFile(*h,
			&winFindData));

	}

	bool Directory::IsEqualExtension(const std::list<std::wstring>& listMask,
		const std::wstring& wsExtension)
	{

		return std::find_if(listMask.cbegin(),
			listMask.cend(),
			[wsExtension](const std::wstring& wsMask)
		{

			return wsExtension == Convert::ToLower(wsMask);

		}) != listMask.cend();
		
	}

}

