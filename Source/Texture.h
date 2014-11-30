#pragma once

#include "Vector2.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	static std::shared_ptr<Texture> load(std::string path);
	void free();
	void render(Vector2 position);
	int width(){ return w; }
	int height(){ return h; }

private:
	SDL_Texture* texture;

	static std::unordered_map<std::string, std::weak_ptr<Texture>> textureMap;

	int w, h;
};

