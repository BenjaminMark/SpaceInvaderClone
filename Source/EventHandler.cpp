#include "EventHandler.h"
#include "SpaceEventType.h"
#include "InputEvent.h"
#include <stdint.h>

std::unordered_map<SpaceEventType, std::list<std::weak_ptr<GameObject>>> EventHandler::observers;
std::queue<std::shared_ptr<SpaceEvent>> EventHandler::eventQueue;


EventHandler::EventHandler()
{
	
}

EventHandler::~EventHandler()
{

}

int EventHandler::handleEvents()
{
	if (handleInput()){
		return -1;
	}

	while(!eventQueue.empty()){
		std::shared_ptr<SpaceEvent> curEvent = eventQueue.front();
		eventQueue.pop();
		if (curEvent->type == EVENT_GAMEOVER){
			return 0;
		}

		auto recipients = observers.find(curEvent->type);

		if (recipients != observers.end()){
			for (auto it = recipients->second.begin(); it != recipients->second.end(); ){
				if (it->expired()){
					it = recipients->second.erase(it);
					continue;
				}
				else {
					it->lock()->notify(curEvent);
					++it;
				}
			}
		}
	}
	return 1;
}

void EventHandler::registerObserver(std::weak_ptr<GameObject> object, SpaceEventType type)
{
	if (observers.count(type) == 0){
		std::list<std::weak_ptr<GameObject>> tempList;

		tempList.push_back(object);
		
		observers.emplace(type, tempList);
	}
	else {
		auto curObservers = observers.find(type);
		curObservers->second.push_back(object);
	}
}

void EventHandler::raiseEvent(std::shared_ptr<SpaceEvent> e)
{
	eventQueue.push(e);
}

bool EventHandler::handleInput()
{
	SDL_Event* input = new SDL_Event();

	while (SDL_PollEvent(input) != 0){
		InputEvent* e = new InputEvent();

		if (input->type == SDL_QUIT){
			return true; //Quit == true
		}
		else {
			std::unique_ptr<SDL_Event> inputPtr(input);
			e->input = std::move(inputPtr);
			eventQueue.push(std::shared_ptr<SpaceEvent>(e));
		}
		input = new SDL_Event();
	}
	return false;
}

void EventHandler::flushEvents()
{
	while (!eventQueue.empty()){
		eventQueue.pop();
	}
}