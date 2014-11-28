#include "GameObject.h"
#include "SpaceInvaderClone.h"

std::unordered_multimap<LayerType, std::shared_ptr<GameObject>> GameObject::gameObjectList;

GameObject::GameObject(LayerType layer_) : layer(layer_), alive(true), collides(false)
{
}


GameObject::~GameObject()
{
	
}

void GameObject::update()
{

}

void GameObject::render()
{
	if (texture){
		texture->render(position);
	}
}

void GameObject::notify(std::shared_ptr<SpaceEvent> e)
{
	eventQueue.push(e);
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

	for (int i = 0; i < NUM_LAYERS; ++i){
		auto pair = gameObjectList.equal_range((LayerType)i);
		for (auto it = pair.first; it != pair.second; ++it){
			it->second->render();
		}
		
	}

	SDL_RenderPresent(SpaceInvaderClone::renderer);
}
