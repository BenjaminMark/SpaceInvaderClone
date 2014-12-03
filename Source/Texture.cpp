#include "Texture.h"
#include "SpaceInvaderClone.h"
#include <math.h>

std::unordered_map<std::string, std::weak_ptr<Texture>> Texture::textureMap;
SDL_Window* Texture::window = nullptr;
SDL_Renderer* Texture::renderer = nullptr;
TTF_Font* Texture::scoreFont = nullptr;


Texture::Texture() : texture(nullptr), w(0), h(0), path("")
{

}


Texture::~Texture()
{
	free();
}

std::shared_ptr<Texture> Texture::load(std::string path)
{
	int textureFound = textureMap.count(path);
	auto curTex = textureMap.find(path);
	

	if (textureFound == 0 || (textureFound == 1 && curTex->second.expired())){
		if (textureFound == 1){
			textureMap.erase(curTex);
		}

		SDL_Texture* tempTexture = nullptr;
		std::shared_ptr<Texture> retTex = std::make_shared<Texture>();
		retTex->path = path;

		SDL_Surface* intermediarySurface = IMG_Load(path.c_str());
		if (intermediarySurface == nullptr){
			printf("Error loading image: %s\n", path.c_str(), IMG_GetError());
		}
		else {
			SDL_SetColorKey(intermediarySurface, SDL_TRUE, SDL_MapRGB(intermediarySurface->format, 0, 0xFF, 0xFF));

			tempTexture = SDL_CreateTextureFromSurface(Texture::renderer, intermediarySurface);
			if (tempTexture == nullptr){
				printf("Error creating texture: %s\n", path.c_str(), SDL_GetError());
			}
			else{
				retTex->w = intermediarySurface->w;
				retTex->h = intermediarySurface->h;
			}

			SDL_FreeSurface(intermediarySurface);
		}

		retTex->texture = tempTexture;
		textureMap.emplace(path, std::weak_ptr<Texture>(retTex));

		return retTex;
	}
	else {
		return curTex->second.lock();
	}

	
}

void Texture::free()
{
	if (texture){
		SDL_DestroyTexture(texture);
		texture = nullptr;
		w = 0;
		h = 0;
	}
}

void Texture::render(Vector2 pos, float rotation)
{
	SDL_Rect quad = { static_cast<int>(round(pos.x)), static_cast<int>(round(pos.y)), w, h };
	SDL_RenderCopyEx(Texture::renderer, texture, nullptr, &quad, rotation, nullptr, SDL_FLIP_NONE);
}

void Texture::loadText(std::string text, SDL_Colour colour)
{
	free();

	SDL_Surface* tmpSurface = TTF_RenderText_Blended(scoreFont, text.c_str(), colour);
	if (tmpSurface == nullptr){
		printf("Could not load the the text: %s. Error: %s\n", text, TTF_GetError());
	}
	else{
		texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);

		if (texture == nullptr){
			printf("Could not create texture from text: %s\n", SDL_GetError());
		}
		else {
			w = tmpSurface->w;
			h = tmpSurface->h;
		}
		SDL_FreeSurface(tmpSurface);
	}
}

bool Texture::initRendering()
{
	window = SDL_CreateWindow("Space Attackers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		printf("Error creating window: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		printf("Error creating renderer: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	scoreFont = TTF_OpenFont("Data/Fonts/Arvo-Regular.ttf", 28);

	if (scoreFont == nullptr){
		printf("Failed to load font: %s\n", TTF_GetError());
		return false;
	}
	return true;
}

void Texture::cleanUpRendering()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(scoreFont);
}


void Texture::clearRenderer()
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
}

void Texture::presentRenderer()
{
	SDL_RenderPresent(renderer);
}