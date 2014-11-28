#include "Texture.h"
#include "SpaceInvaderClone.h"


Texture::Texture() : texture(nullptr), w(0), h(0)
{

}


Texture::~Texture()
{
	free();
}

bool Texture::load(std::string path)
{
	free();

	SDL_Texture* tempTexture = nullptr;

	SDL_Surface* intermediarySurface = IMG_Load(path.c_str());
	if (intermediarySurface == nullptr){
		printf("Error loading image: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		SDL_SetColorKey(intermediarySurface, SDL_TRUE, SDL_MapRGB(intermediarySurface->format, 0xFF, 0, 0xFF));

		tempTexture = SDL_CreateTextureFromSurface(SpaceInvaderClone::renderer, intermediarySurface);
		if (tempTexture == nullptr){
			printf("Error creating texture: %s\n", path.c_str(), SDL_GetError());
		}
		else{
			w = intermediarySurface->w;
			h = intermediarySurface->h;
		}
		
		SDL_FreeSurface(intermediarySurface);
	}

	texture = tempTexture;

	return texture != nullptr;
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

void Texture::render(Vector2 pos)
{
	SDL_Rect quad = { pos.x, pos.y, w, h };
	SDL_RenderCopy(SpaceInvaderClone::renderer, texture, nullptr, &quad);
}
