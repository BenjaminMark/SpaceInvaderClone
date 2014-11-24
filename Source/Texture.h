#pragma once

#include "Vector2.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	bool load(std::string path);
	void free();
	void render(Vector2 position);
	int width(){ return w; }
	int height(){ return h; }

private:
	SDL_Texture* texture;

	int w, h;
};

