#pragma once

#include "..\Interfaces\IEvent.h"

namespace Test
{

	class AutoEvent : public IEvent
	{

	protected:

		AutoEvent(const AutoEvent&) = delete;
		AutoEvent(AutoEvent&&) = delete;
		AutoEvent & operator = (const AutoEvent&) = delete;
		AutoEvent & operator = (AutoEvent&&) = delete;
		
	public:

		using IEvent::IEvent;

		void Reset(void) const override;

		static std::unique_ptr<IEvent> Create(LPSECURITY_ATTRIBUTES = {},
			BOOL = {},
			const std::wstring& = {});

	};

}
