#pragma once

#include "Wrap.h"

namespace Test
{

	class MapFile
	{

		MapFile(void) = default;
		MapFile(const MapFile&) = delete;
		MapFile(MapFile&&) = delete;
		MapFile& operator = (const MapFile&) = delete;
		MapFile& operator = (MapFile&&) = delete;

	public:

		struct SettingsCreate
		{

			HANDLE hFile{};
			LPSECURITY_ATTRIBUTES lpSecurityAttributes{};
			DWORD flProtect = { PAGE_READONLY };
			DWORD dwMaximumSizeHigh{};
			DWORD dwMaximumSizeLow{};
			std::wstring wsName{};

		};

		struct SettingsView
		{

			DWORD dwDesiredAccess = { FILE_MAP_READ };
			DWORD dwFileOffsetHigh{};
			DWORD dwFileOffsetLow{};
			SIZE_T dwNumberOfBytesToMap{};

		};

	private:

		SettingsCreate settingsCreate{};
		SettingsView settingsView{};

		using Handle = std::unique_ptr<Wrap::Common::Handle>;

		Handle h{};

		LPVOID lpv{};

		explicit MapFile(const SettingsCreate&);

	public:

		virtual ~MapFile(void) noexcept;

		static std::unique_ptr<MapFile> Create(const SettingsCreate&);
		
	private:

		MapFile& Create(void);

	public:

		MapFile& ViewOfFile(const SettingsView&);
		
		operator LPCBYTE(void) const noexcept;

		MapFile& UnViewOfFile(void) noexcept;

	};

}
