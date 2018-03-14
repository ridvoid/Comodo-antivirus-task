
#include "AutoSetEvent.h"

namespace Test
{

	AutoSetEvent::AutoSetEvent(const Event& event) noexcept : event(event){ }

	AutoSetEvent::~AutoSetEvent(void) noexcept
	{

		try
		{

			this->event->Set();

		}
		catch (...){ }

	}

}
