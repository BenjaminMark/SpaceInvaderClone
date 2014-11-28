#pragma once

#include "Vector2.h"
#include "Texture.h"
#include "LayerType.h"
#include "SpaceEvent.h"
#include <set>
#include <queue>
#include <memory>
#include <unordered_map>

/*
* The base for every object in the game.
*/
class GameObject
{
public:
	//List of all game objects. Used for rendering, updating and collisions.
	static std::unordered_multimap<LayerType, std::shared_ptr<GameObject>> gameObjectList;

	LayerType layer;
	Vector2 position;
	Vector2 dimensions;
	bool collisionEnabled;

	GameObject(LayerType layer_);
	virtual ~GameObject();

	static void updateAll();
	static void renderAll();

	virtual void update() = 0;
	virtual void render();
	bool checkCollision(std::shared_ptr<const GameObject> other);
	void notify(std::shared_ptr<SpaceEvent> e);
	bool isDead(){ return !alive; }

	
	
	
protected:

	std::shared_ptr<Texture> texture;

	std::queue<std::shared_ptr<SpaceEvent>> eventQueue;

	virtual void move(const Vector2 direction);

	bool alive;
		
};