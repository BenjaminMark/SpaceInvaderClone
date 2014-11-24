#pragma once

#include "SDL.h"
#include "GameObject.h"
#include <unordered_map>
#include <list>

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	bool handleInput();
	void registerObserver(GameObject* object, SDL_EventType type);
	void removeObserver(GameObject* object, SDL_EventType type);

private:
	static std::unordered_map<SDL_EventType, std::list<GameObject*>> inputObservers;
};