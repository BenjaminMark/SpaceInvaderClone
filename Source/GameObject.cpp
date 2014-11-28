#include "GameObject.h"
#include "SpaceInvaderClone.h"
#include "CollisionEvent.h"

std::unordered_multimap<LayerType, std::shared_ptr<GameObject>> GameObject::gameObjectList;

GameObject::GameObject(LayerType layer_) : layer(layer_), alive(true), collisionEnabled(false)
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

void GameObject::move(const Vector2 direction)
{
	Vector2 newPos = position + direction;

	//Clamp values to fit on screen
	if (newPos.x < 0)
		newPos.x = 0;
	if (newPos.y < 0)
		newPos.y = 0;
	if (newPos.x + dimensions.x >= WINDOW_WIDTH)
		newPos.x = WINDOW_WIDTH - dimensions.x;
	if (newPos.y + dimensions.y >= WINDOW_HEIGHT)
		newPos.y = WINDOW_HEIGHT - dimensions.y;

	if (!collisionEnabled){
		position = newPos;
		return;
	}

	for (auto pair : GameObject::gameObjectList){
		if (pair.second.get() != this && checkCollision(pair.second)){
			//Notify ourself that we've collided with something
			CollisionEvent* selfEvent = new CollisionEvent();
			selfEvent->senderLayer = pair.second->layer;
			std::shared_ptr<SpaceEvent> packagedSelfEvent(selfEvent);
			notify(packagedSelfEvent);

			//Notify the other object that they've been collided with
			CollisionEvent* otherEvent = new CollisionEvent();
			otherEvent->senderLayer = layer;
			std::shared_ptr<SpaceEvent> packagedOtherEvent(otherEvent);
			pair.second->notify(packagedOtherEvent);

			//Move back enough to not be colliding.
			if (abs(direction.x) > abs(direction.y)){
				if (direction.x < 0){
					newPos.x += (pair.second->position.x + pair.second->dimensions.x) - newPos.x;
				}
				else {
					newPos.x += pair.second->position.x - (newPos.x + dimensions.x);
				}
			}
			else {
				if (direction.y < 0){
					newPos.y += (pair.second->position.y + pair.second->dimensions.y) - newPos.y;
				}
				else {
					newPos.y += pair.second->position.y - (newPos.y + dimensions.y);
				}
			}
		}
	}

	position = newPos;
}

bool GameObject::checkCollision(std::shared_ptr<const GameObject> other)
{
	if (!other->collisionEnabled){
		return false;
	}

	int left = position.x;
	int right = position.x + dimensions.x;
	int top = position.y;
	int bottom = position.y + dimensions.y;

	int otherLeft = other->position.x;
	int otherRight = other->position.x + other->dimensions.x;
	int otherTop = other->position.y;
	int otherBottom = other->position.y + other->dimensions.y;

	return !(right < otherLeft
		|| left > otherRight
		|| bottom < otherTop
		|| top > otherBottom);

}


void GameObject::updateAll()
{
	for (auto it = gameObjectList.begin(); it != gameObjectList.end(); ++it){
		if (it->second->isDead()){
			it = gameObjectList.erase(it);
		}
		else {
			it->second->update();
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