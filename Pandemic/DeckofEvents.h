#pragma once

#include <vector>
#include <memory>

#include "EventCard.h"

namespace event
{
	std::vector<std::unique_ptr<EventCard>> cards();
}
