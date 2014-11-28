#include "Player.h"
#include "EventHandler.h"
#include "InputEvent.h"
#include "Constants.h"

std::vector<std::shared_ptr<Texture>> Player::playerTextures;

Player::Player(PlayerTextureType texture_) : GameObject(LAYER_ACTORS)
{
	texture = playerTextures[texture_];
	collisionEnabled = true;
}


Player::~Player()
{

}

void Player::update()
{
	while (!eventQueue.empty()){
		auto curEvent = eventQueue.front();
		eventQueue.pop();

		if (curEvent->type == EVENT_INPUT){
			std::shared_ptr<InputEvent> inputEvent = std::dynamic_pointer_cast<InputEvent>(curEvent);
			handleInput(inputEvent);
		}
	}

	movePlayer();
}

void Player::newPlayer(PlayerTextureType texType)
{
	std::shared_ptr<GameObject> object = std::make_shared<Player>(texType);
	gameObjectList.emplace(object->layer, object);

	EventHandler::registerObserver(std::weak_ptr<GameObject>(object), EVENT_INPUT);
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
		default:
			break;
		}
	}
}

void Player::movePlayer(){
	SDL_PumpEvents();
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A]){
		move(Vector2(-PLAYER_SPEED, 0));
	}
	if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D]){
		move(Vector2(PLAYER_SPEED, 0));
	}
}