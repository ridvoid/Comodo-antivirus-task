#pragma once

#include "MapFile.h"

namespace Test
{

	MapFile::MapFile(const SettingsCreate& settingsCreate) : MapFile()
	{

		this->h = Wrap::Common::Handle::Create<Wrap::Common::Handle>({});
		this->settingsCreate = settingsCreate;

	}

	MapFile::~MapFile(void) noexcept
	{

		this->UnViewOfFile();

	}

	std::unique_ptr<MapFile> MapFile::Create(const SettingsCreate& settingsCreate)
	{

		std::unique_ptr<MapFile> uptrReturn(new MapFile(settingsCreate));

		uptrReturn->Create();

		return uptrReturn;

	}

	MapFile& MapFile::Create(void)
	{

		this->h = Wrap::Common::Handle::Create<Wrap::Common::Handle>(CreateFileMapping(this->settingsCreate.hFile,
			this->settingsCreate.lpSecurityAttributes,
			this->settingsCreate.flProtect,
			this->settingsCreate.dwMaximumSizeHigh,
			this->settingsCreate.dwMaximumSizeLow,
			this->settingsCreate.wsName.c_str()));
		if (!*this->h)
			throw MapFileException(L"Error CreateFileMapping",
				GetLastError());

		return *this;

	}

	MapFile& MapFile::ViewOfFile(const SettingsView& settingsView)
	{

		this->UnViewOfFile().lpv = MapViewOfFile(*this->h,
			settingsView.dwDesiredAccess,
			settingsView.dwFileOffsetHigh,
			settingsView.dwFileOffsetLow,
			settingsView.dwNumberOfBytesToMap);
		if (!this->lpv)
			throw MapFileException(L"Error MapViewOfFile",
				GetLastError());

		return *this;

	}

	MapFile::operator LPCBYTE(void) const noexcept
	{

		return reinterpret_cast<LPCBYTE>(this->lpv);

	}

	MapFile& MapFile::UnViewOfFile(void) noexcept
	{

		if (!this->lpv)
			return *this;

		UnmapViewOfFile(this->lpv);

		this->lpv = nullptr;

		return *this;

	}

}
