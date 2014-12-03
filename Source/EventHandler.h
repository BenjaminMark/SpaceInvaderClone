#pragma once

#include "SDL.h"
#include "GameObject.h"
#include "SpaceEvent.h"
#include <unordered_map>
#include <list>
#include <queue>
#include <memory>

class EventHandler
{
public:
	EventHandler();
	~EventHandler();
	int handleEvents();
	static void registerObserver(std::weak_ptr<GameObject> object, SpaceEventType type);
	static void raiseEvent(std::shared_ptr<SpaceEvent> e);
	static void flushEvents();

private:
	static std::unordered_map<SpaceEventType, std::list<std::weak_ptr<GameObject>>> observers;
	static std::queue<std::shared_ptr<SpaceEvent>> eventQueue;
	bool handleInput();
};