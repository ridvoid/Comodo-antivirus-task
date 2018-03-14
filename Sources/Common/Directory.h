#pragma once
#include "Exceptions.h"
#include "Wrap.h"
#include "File.h"
#include "Convert.h"

namespace Test
{

	class Directory
	{

		Directory(void) = delete;
		Directory(const Directory&) = delete;
		Directory(Directory&&) = delete;
		Directory& operator = (const Directory&) = delete;
		Directory& operator = (Directory&&) = delete;
		~Directory(void) = delete;

	public:

		static std::list<std::wstring> GetFiles(const std::wstring&,
			const std::list<std::wstring>&,
			bool = true);

	private:

		static void GetFiles(std::list<std::wstring>&, 
			const std::wstring&,
			const std::list<std::wstring>&,
			bool = true);

		static bool IsEqualExtension(const std::list<std::wstring>&,
			const std::wstring&);

	};

}

