
#include "AutoEvent.h"

namespace Test
{

	void AutoEvent::Reset(void) const
	{

		throw AutoEventException(L"Error AutoEvent::Reset",
			ERROR_NOT_SUPPORTED);

	}

	std::unique_ptr<IEvent> AutoEvent::Create(LPSECURITY_ATTRIBUTES lpSecAttr,
		BOOL bInitialState,
		const std::wstring& wsName)
	{

		return IEvent::Create<AutoEvent>(lpSecAttr,
			FALSE,
			bInitialState,
			wsName);

	}

}
