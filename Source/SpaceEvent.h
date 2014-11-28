#pragma once

#include "SDL.h"
#include "SpaceEventType.h"

class SpaceEvent
{
public:
	const SpaceEventType type;

	virtual ~SpaceEvent();

protected:
	SpaceEvent(SpaceEventType type_);
};

