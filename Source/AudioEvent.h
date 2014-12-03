#pragma once

#include "SpaceEvent.h"
#include "SoundType.h"

class AudioEvent : public SpaceEvent
{
public:
	const SoundType type;

	AudioEvent(SoundType type);
	~AudioEvent();
};

