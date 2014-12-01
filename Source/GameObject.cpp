#include "GameObject.h"
#include "SpaceInvaderClone.h"
#include "CollisionEvent.h"

std::unordered_multimap<LayerType, std::shared_ptr<GameObject>> GameObject::gameObjectList;

GameObject::GameObject(LayerType layer_) : layer(layer_), alive(true), collisionEnabled(false)
{
	texture = std::make_shared<Texture>();
}

GameObject::GameObject(LayerType layer_, std::shared_ptr<Texture> texture_, bool collisionEnabled_, Vector2 startPos)
	: layer(layer_), texture(texture_), collisionEnabled(collisionEnabled_), alive(true), hasMoved(false)
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
	hasMoved = true;
	lastPosition = position;

	position += direction;
}

void GameObject::handleCollisions(std::shared_ptr<GameObject> object)
{
	
	

	bool outofbounds = false;

	//Clamp values to fit on screen
	if (object->position.x < 0){
		object->position.x = 0;
		outofbounds = true;
	}
	if (object->position.y < 0){
		object->position.y = 0;
		outofbounds = true;
	}
	if (object->position.x + object->dimensions.x >= WINDOW_WIDTH){
		object->position.x = WINDOW_WIDTH - object->dimensions.x;
		outofbounds = true;
	}
	if (object->position.y + object->dimensions.y >= WINDOW_HEIGHT){
		object->position.y = WINDOW_HEIGHT - object->dimensions.y;
		outofbounds = true;
	}

	if (outofbounds){
		object->notify(std::make_shared<CollisionEvent>(LAYER_BACKGROUND));
	}

	if (!object->collisionEnabled){
		return;
	}

	for (auto pair : GameObject::gameObjectList){
		if (pair.second != object && checkCollision(object, pair.second)){


			if (!pair.second->hasMoved){//Avoids getting duplicate collision events
				//Notify ourself that we've collided with something
				object->notify(std::make_shared<CollisionEvent>(pair.second->layer));
			}

			//Notify the other object that they've been collided with
			pair.second->notify(std::make_shared<CollisionEvent>(object->layer));


			/*
			//Move back enough to not be colliding.
			if (abs(object->lastDirection.x) > abs(object->lastDirection.y)){
				if (object->lastDirection.x < 0){
					//object->position.x += (pair.second->position.x + pair.second->dimensions.x) - object->position.x;
				}
				else {
					//object->position.x += pair.second->position.x - (object->position.x + object->dimensions.x);
				}
			}
			else {
				if (object->lastDirection.y < 0){
					//object->position.y += (pair.second->position.y + pair.second->dimensions.y) - object->position.y;
				}
				else {
					//object->position.y += pair.second->position.y - (object->position.y + object->dimensions.y);
				}
			}
			*/
		}
	}
}

bool GameObject::checkCollision(std::shared_ptr<const GameObject> lhs, std::shared_ptr<const GameObject> rhs)
{
	if (!(lhs->collisionEnabled && rhs->collisionEnabled)){
		return false;
	}

	int left = lhs->position.x;
	int right = lhs->position.x + lhs->dimensions.x;
	int top = lhs->position.y;
	int bottom = lhs->position.y + lhs->dimensions.y;

	int otherLeft = rhs->position.x;
	int otherRight = rhs->position.x + rhs->dimensions.x;
	int otherTop = rhs->position.y;
	int otherBottom = rhs->position.y + rhs->dimensions.y;

	return !(right < otherLeft
		|| left > otherRight
		|| bottom < otherTop
		|| top > otherBottom);

}


void GameObject::updateAll()
{
	for (auto it = gameObjectList.begin(); it != gameObjectList.end(); ++it){
		it->second->update();
	}

	//Check for collisions
	for (auto it = gameObjectList.begin(); it != gameObjectList.end(); ++it){
		if (it->second->hasMoved){
			handleCollisions(it->second);
		}
	}

	for (auto it = gameObjectList.begin(); it != gameObjectList.end(); ){
		if (it->second->isDead()){
			it = gameObjectList.erase(it);
		}
		else {
			it->second->hasMoved = false;
			++it;
		}
	}
}

void GameObject::renderAll()
{
	Texture::clearRenderer();

	for (int i = 0; i < NUM_LAYERS; ++i){
		auto pair = gameObjectList.equal_range((LayerType)i);
		for (auto it = pair.first; it != pair.second; ++it){
			it->second->render();
		}
		
	}

	Texture::presentRenderer();
}

void GameObject::registerObject(std::shared_ptr<GameObject> object){
	gameObjectList.emplace(object->layer, object);
}