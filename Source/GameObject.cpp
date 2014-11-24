#include "GameObject.h"
#include "SpaceInvaderClone.h"

std::unordered_multimap<LayerType, std::shared_ptr<GameObject>> GameObject::gameObjectList = std::unordered_multimap < LayerType, std::shared_ptr<GameObject>>();

GameObject::GameObject(LayerType layer_) : layer(layer_), texture(nullptr), position(Vector2(0, 0)), alive(true), collides(false)
{
	gameObjectList.emplace(layer_, std::shared_ptr<GameObject>(this));
}


GameObject::~GameObject()
{
	
}

void GameObject::update()
{

}

void GameObject::render()
{
	if (texture != nullptr){
		texture->render(position);
	}
}

void GameObject::notify(const SDL_Event &e)
{
	inputQueue.push(&e);
}


void GameObject::updateAll()
{
	for (std::pair<LayerType, std::shared_ptr<GameObject>> pair : gameObjectList){
		pair.second->update();
	}

	for (auto it = gameObjectList.begin(); it != gameObjectList.end(); ++it){
		if (it->second->isDead()){
			it = gameObjectList.erase(it);
		}
	}
}

void GameObject::renderAll()
{
	SDL_SetRenderDrawColor(SpaceInvaderClone::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(SpaceInvaderClone::renderer);

	for (std::pair<LayerType, std::shared_ptr<GameObject>> pair : gameObjectList){
		pair.second->render();
	}

	SDL_RenderPresent(SpaceInvaderClone::renderer);
}