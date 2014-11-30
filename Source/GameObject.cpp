#include "GameObject.h"
#include "SpaceInvaderClone.h"
#include "CollisionEvent.h"

std::unordered_multimap<LayerType, std::shared_ptr<GameObject>> GameObject::gameObjectList;

GameObject::GameObject(LayerType layer_) : layer(layer_), alive(true), collisionEnabled(false)
{

}

GameObject::GameObject(LayerType layer_, std::shared_ptr<Texture> texture_, bool collisionEnabled_, Vector2 startPos)
	: layer(layer_), texture(texture_), collisionEnabled(collisionEnabled_), alive(true)
{
	dimensions = Vector2(texture->width(), texture->height());
	move(startPos);
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
	bool outofbounds = false;

	//Clamp values to fit on screen
	if (newPos.x < 0){
		newPos.x = 0;
		outofbounds = true;
	}
	if (newPos.y < 0){
		newPos.y = 0;
		outofbounds = true;
	}
	if (newPos.x + dimensions.x >= WINDOW_WIDTH){
		newPos.x = WINDOW_WIDTH - dimensions.x;
		outofbounds = true;
	}
	if (newPos.y + dimensions.y >= WINDOW_HEIGHT){
		newPos.y = WINDOW_HEIGHT - dimensions.y;
		outofbounds = true;
	}

	if (outofbounds){
		notify(std::make_shared<CollisionEvent>(LAYER_BACKGROUND));
	}

	if (!collisionEnabled){
		position = newPos;
		return;
	}

	for (auto pair : GameObject::gameObjectList){
		if (pair.second.get() != this && checkCollision(pair.second)){

			//Notify ourself that we've collided with something
			notify(std::make_shared<CollisionEvent>(pair.second->layer));

			//Notify the other object that they've been collided with
			pair.second->notify(std::make_shared<CollisionEvent>(layer));


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
	for (auto it = gameObjectList.begin(); it != gameObjectList.end(); ){
		if (it->second->isDead()){
			it = gameObjectList.erase(it);
		}
		else {
			it->second->update();
			++it;
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

void GameObject::registerObject(std::shared_ptr<GameObject> object){
	gameObjectList.emplace(object->layer, object);
}