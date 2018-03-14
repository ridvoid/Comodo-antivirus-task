#pragma once

#include "..\Interfaces\IFile.h"

namespace Test
{

	class NamedPipe : public IFile
	{

		NamedPipe(void) = default;
		NamedPipe(const NamedPipe&) = delete;
		NamedPipe(NamedPipe&&) = delete;
		NamedPipe& operator = (const NamedPipe&) = delete;
		NamedPipe& operator = (NamedPipe&&) = delete;
		
	public:

		struct Settings
		{

			std::wstring wsName{};
			DWORD dwOpenMode{};
			DWORD dwPipeMode{};
			DWORD nMaxInstances{};
			DWORD nOutBufferSize{};
			DWORD nInBufferSize{};
			DWORD nDefaultTimeOut{};
			LPSECURITY_ATTRIBUTES lpSecurityAttributes{};
		
		};

	private:

		Settings settings{};

	public:

		explicit NamedPipe(const Settings&);

		virtual ~NamedPipe(void) = default;

		static std::unique_ptr<IFile> Create(const Settings&);

	private:

		IFile& Create(void) override;

	public:

		IFile& Connect(LPOVERLAPPED = {}) const override;

		IFile& Disconnect(void) const override;

	private:

		LARGE_INTEGER GetSize(void) const override;

	};

}
