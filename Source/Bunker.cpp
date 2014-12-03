#include "Bunker.h"
#include <string>
#include "EventHandler.h"
#include "Constants.h"


Bunker::Bunker(std::string texturePath, Vector2 startPos) : GameObject(LAYER_BUNKER, Texture::load(texturePath), true, startPos), lives(BUNKER_NUMLIVES), destructionState(0)
{
}


Bunker::~Bunker()
{
}

void Bunker::newBunker(std::string texturePath, Vector2 startPos)
{
	std::shared_ptr<Bunker> bunker = std::make_shared<Bunker>(texturePath, startPos);
	GameObject::registerObject(bunker);
}

void Bunker::update()
{
	while (!eventQueue.empty()){
		auto curEvent = eventQueue.front();
		eventQueue.pop();

		if (curEvent->type == EVENT_COLLISION){
			if (lives > 0){
				lives--;
				if (lives > 0 && lives % 3 == 0){
					destructionState++;
					texture = Texture::load("Data/Bunkers/Bunker_" + std::to_string(destructionState) + ".png");
				}
			}
			else {
				alive = false;
				collisionEnabled = false;
			}
		}
	}
}