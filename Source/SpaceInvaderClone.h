#pragma once

#include "EventHandler.h"
#include "Constants.h"

class SpaceInvaderClone
{
public:
	static SDL_Window* window;
	static SDL_Renderer* renderer;

	SpaceInvaderClone();
	~SpaceInvaderClone();

	int run();

private:
	EventHandler inputhandler;

	bool init();
	void cleanUp();
	void initObjects();
};

