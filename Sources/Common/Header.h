#pragma once
#include <Windows.h>
#include <exception>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <mutex>
#include <map>
#include <functional>
#include <fstream>
#include <regex>
#include <cctype>
#include <list>
#include <thread>

using LPCBYTE = const unsigned char*;

namespace Test
{

	namespace Constants
	{

		enum Cpu : DWORD { Multiplier = 2 };

		const std::wstring wsNamePipe(L"\\\\.\\pipe\\{40BABB7D-7842-44AE-AF0E-8ED740AA881F}");

		enum SizeBuffers : std::size_t { Pipe = 65535 };

		const std::wstring wsVirus(L"Virus");

		const std::wstring wsNormal(L"Normal");

	}

}
