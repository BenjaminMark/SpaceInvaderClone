#include "InputHandler.h"

std::unordered_map<SDL_EventType, std::list<GameObject*>> InputHandler::inputObservers = std::unordered_map<SDL_EventType, std::list<GameObject*>>();


InputHandler::InputHandler()
{
	
}

InputHandler::~InputHandler()
{

}

bool InputHandler::handleInput()
{
	SDL_Event curEvent;

	while (SDL_PollEvent(&curEvent) != 0){
		if (curEvent.type == SDL_QUIT){
			return true; //Quit = true
		} 
		else {
			auto observers = inputObservers.find((SDL_EventType)curEvent.type);

			if (observers != inputObservers.end()){
				for (GameObject* object : observers->second){
					object->notify(curEvent);
				}
			}
		}
	}
	return false;
}

void InputHandler::registerObserver(GameObject* object, SDL_EventType type)
{
	if (inputObservers.count(type) == 0){
		std::list<GameObject*> tempList = std::list<GameObject*>();
		tempList.push_back(object);
		
		inputObservers.emplace(type, tempList);
	}
	else {
		auto observers = inputObservers.find(type);
		observers->second.push_back(object);
	}
}

void InputHandler::removeObserver(GameObject* object, SDL_EventType type)
{
	auto observers = inputObservers.find(type);

	if (observers == inputObservers.end()){
		return;
	}
	else {
		observers->second.remove(object);
	}
}