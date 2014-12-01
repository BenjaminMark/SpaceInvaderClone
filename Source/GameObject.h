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

	void notify(std::shared_ptr<SpaceEvent> e);
	bool isDead(){ return !alive; }

	
	
	
protected:
	GameObject(LayerType layer_, std::shared_ptr<Texture> texture_, bool collisionenabled_, Vector2 startPos);
	std::shared_ptr<Texture> texture;
	std::queue<std::shared_ptr<SpaceEvent>> eventQueue;

	static void registerObject(std::shared_ptr<GameObject> object);
	static void handleCollisions(std::shared_ptr<GameObject> object);
	static bool checkCollision(std::shared_ptr<const GameObject> lhs, std::shared_ptr<const GameObject> rhs);
	virtual void move(const Vector2 direction);
	

	bool alive;
	bool hasMoved;
	Vector2 lastPosition;

private:
	//List of all game objects. Used for rendering, updating and collisions
	static std::unordered_multimap<LayerType, std::shared_ptr<GameObject>> gameObjectList;
};