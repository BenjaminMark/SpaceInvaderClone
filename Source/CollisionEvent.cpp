#include "CollisionEvent.h"


CollisionEvent::CollisionEvent(LayerType senderLayer_) : SpaceEvent(EVENT_COLLISION), senderLayer(senderLayer_)
{
}


CollisionEvent::~CollisionEvent()
{
}
