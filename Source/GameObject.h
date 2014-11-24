#pragma once

#include "Vector2.h"
#include "Texture.h"
#include "LayerType.h"
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

	GameObject(LayerType layer_);
	virtual ~GameObject();

	static void updateAll();
	static void renderAll();

	virtual void update();
	virtual void render();
	void notify(const SDL_Event &e);
	Vector2 getPosition() { return position; }
	bool isDead(){ return !alive; }

	bool collisionsEnabled(){ return collides; }
	void enableCollisions(){ collides = true; }
	void disableCollisions(){ collides = false; }
	
protected:
	//List of all game objects. Used for rendering, updating and collisions.
	static std::unordered_multimap<LayerType, std::shared_ptr<GameObject>> gameObjectList;

	Texture* texture;

	std::queue<const SDL_Event*> inputQueue;

	Vector2 position;
	bool alive;
	bool collides;
		
};