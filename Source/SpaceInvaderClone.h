#pragma once

#include "InputHandler.h"
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
	InputHandler inputhandler;

	bool init();
	void cleanUp();
	void handleTextures(bool cleanUp);
	void initObjects();
};

