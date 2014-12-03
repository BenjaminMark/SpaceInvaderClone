#include "AudioEvent.h"


AudioEvent::AudioEvent(SoundType type_) : SpaceEvent(EVENT_AUDIO), type(type_)
{
}


AudioEvent::~AudioEvent()
{
}
