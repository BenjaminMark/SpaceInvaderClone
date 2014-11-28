#include "Player.h"
#include "EventHandler.h"
#include "InputEvent.h"
#include "Constants.h"

std::vector<std::shared_ptr<Texture>> Player::playerTextures;

Player::Player(PlayerTextureType texture_) : GameObject(LAYER_ACTORS)
{
	texture = playerTextures[texture_];
	collides = true;
}


Player::~Player()
{

}

void Player::update()
{
	while (!eventQueue.empty()){
		auto curEvent = eventQueue.front();
		eventQueue.pop();

		if (curEvent->type == INPUT_EVENT){
			std::shared_ptr<InputEvent> inputEvent = std::dynamic_pointer_cast<InputEvent>(curEvent);
			handleInput(inputEvent);
		}
	}
}

void Player::newPlayer(PlayerTextureType texType)
{
	std::shared_ptr<GameObject> object = std::make_shared<Player>(texType);
	gameObjectList.emplace(object->layer, object);

	EventHandler::registerObserver(std::weak_ptr<GameObject>(object), INPUT_EVENT);
}

bool Player::loadTextures(std::string basePath)
{
	for (int i = 0; i < NUM_PLAYERTEXTURES; ++i){
		std::shared_ptr<Texture> texPtr = std::make_shared<Texture>();
		
		if (!(texPtr->load(basePath + "_" + std::to_string(i) + ".png"))){
			printf("Failed to Load Player Texture: %d", i);
			return false;
		}
		else {
			playerTextures.push_back(texPtr);
		}
	}
	return true;
}

void Player::cleanTextures()
{
	playerTextures.clear();
}

void Player::handleInput(std::shared_ptr<InputEvent> inputEvent)
{
	if (inputEvent.use_count() != 0 && inputEvent->input->type == SDL_KEYDOWN){
		switch (inputEvent->input->key.keysym.sym)
		{
		case SDLK_DOWN:
			position = Vector2(WINDOW_WIDTH/2, WINDOW_HEIGHT/2); 
			break;
		case SDLK_UP:
			position = Vector2();
			break;
		default:
			break;
		}
	}
}