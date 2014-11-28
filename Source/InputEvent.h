#pragma once

#include "SpaceEvent.h"
#include <memory>

class InputEvent : public SpaceEvent
{
public:
	std::unique_ptr<const SDL_Event> input;

	InputEvent();
	~InputEvent();
};

