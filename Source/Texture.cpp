#include "Texture.h"
#include "SpaceInvaderClone.h"

std::unordered_map<std::string, std::weak_ptr<Texture>> Texture::textureMap;


Texture::Texture() : texture(nullptr), w(0), h(0)
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

		SDL_Surface* intermediarySurface = IMG_Load(path.c_str());
		if (intermediarySurface == nullptr){
			printf("Error loading image: %s\n", path.c_str(), IMG_GetError());
		}
		else {
			SDL_SetColorKey(intermediarySurface, SDL_TRUE, SDL_MapRGB(intermediarySurface->format, 0, 0xFF, 0xFF));

			tempTexture = SDL_CreateTextureFromSurface(SpaceInvaderClone::renderer, intermediarySurface);
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

void Texture::render(Vector2 pos)
{
	SDL_Rect quad = { pos.x, pos.y, w, h };
	SDL_RenderCopy(SpaceInvaderClone::renderer, texture, nullptr, &quad);
}
