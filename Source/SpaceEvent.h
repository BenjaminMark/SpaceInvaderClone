#pragma once

#include "SDL.h"
#include "SpaceEventType.h"

class SpaceEvent
{
public:
	SpaceEvent(SpaceEventType type_);
	const SpaceEventType type;

	virtual ~SpaceEvent();
};

