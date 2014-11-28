#pragma once

#include "SpaceEvent.h"
#include <memory>
#include "GameObject.h"

class CollisionEvent : public SpaceEvent
{
public:
	LayerType senderLayer;

	CollisionEvent();
	virtual ~CollisionEvent();
};

