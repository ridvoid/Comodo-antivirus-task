#pragma once

#include "..\Common\Header.h"

namespace Test
{

	class IDbSignatures
	{

		IDbSignatures(const IDbSignatures&) = delete;
		IDbSignatures(IDbSignatures&&) = delete;
		IDbSignatures& operator = (const IDbSignatures&) = delete;
		IDbSignatures& operator = (IDbSignatures&&) = delete;

	protected:

		IDbSignatures(void) = default;

	public:

		virtual ~IDbSignatures(void) = default;

		virtual IDbSignatures& Load(void) = 0;

		virtual std::vector<BYTE> Check(LPCBYTE,
			std::size_t) = 0;

	};

}