#pragma once

#include "..\Interfaces\IEvent.h"

namespace Test
{

	class AutoSetEvent
	{

		AutoSetEvent(void) = delete;
		AutoSetEvent(const AutoSetEvent&) = delete;
		AutoSetEvent(AutoSetEvent&&) = delete;
		AutoSetEvent& operator = (const AutoSetEvent&) = delete;
		AutoSetEvent& operator = (AutoSetEvent&&) = delete;

		using Event = std::unique_ptr<IEvent>;
		const Event& event;

	public:

		explicit AutoSetEvent(const Event&) noexcept;

		~AutoSetEvent(void) noexcept;

	};

}
