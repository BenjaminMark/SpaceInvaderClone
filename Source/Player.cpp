#include "Player.h"
#include "EventHandler.h"
#include "InputEvent.h"
#include "Constants.h"
#include <string>
#include "Projectile.h"


Player::Player(std::string texturePath, Vector2 startPos) : GameObject(LAYER_PLAYER, Texture::load(texturePath), true, startPos)
{

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

void Player::newPlayer(std::string texturePath, Vector2 startPos)
{
	std::shared_ptr<GameObject> object = std::make_shared<Player>(texturePath, startPos);
	GameObject::registerObject(object);

	EventHandler::registerObserver(std::weak_ptr<GameObject>(object), EVENT_INPUT);
}

void Player::handleInput(std::shared_ptr<InputEvent> inputEvent)
{
	if (inputEvent.use_count() != 0 && inputEvent->input->type == SDL_KEYDOWN){
		switch (inputEvent->input->key.keysym.sym)
		{
		case SDLK_SPACE:
			Projectile::newProjectile("Data/Projectiles/projectile_0.png",Vector2(position.x+dimensions.x/2, position.y-20),Vector2(0,-1));
			break;
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