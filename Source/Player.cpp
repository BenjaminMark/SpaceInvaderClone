#include "Player.h"
#include "EventHandler.h"
#include "InputEvent.h"
#include "Constants.h"
#include <string>
#include "Projectile.h"
#include "ScoreEvent.h"
#include "CollisionEvent.h"
#include "ExplosiveProjectile.h"
#include "AudioEvent.h"

UpgradeState Player::upgradeState = USTATE_DEFAULT;

Player::Player(std::string texturePath, Vector2 startPos) : GameObject(LAYER_PLAYER, Texture::load(texturePath), true, startPos), detonate(false)
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
		else if(curEvent->type == EVENT_COLLISION){
			std::shared_ptr<CollisionEvent> colEvent = std::dynamic_pointer_cast<CollisionEvent>(curEvent);

			if (colEvent->senderLayer != LAYER_BACKGROUND){ //The player shouldnt lose lives when hitting the edge of the screen
				EventHandler::raiseEvent(std::make_shared<ScoreEvent>(true, 0));
			}
		}
	}

	movePlayer();
}

std::weak_ptr<Player> Player::newPlayer(std::string texturePath, Vector2 startPos)
{
	std::shared_ptr<Player> object = std::make_shared<Player>(texturePath, startPos);
	GameObject::registerObject(object);

	EventHandler::registerObserver(std::weak_ptr<GameObject>(object), EVENT_INPUT);
	return std::weak_ptr<Player>(object);
}

void Player::handleInput(std::shared_ptr<InputEvent> inputEvent)
{
	if (inputEvent.use_count() != 0 && inputEvent->input->type == SDL_KEYDOWN){
		switch (inputEvent->input->key.keysym.sym)
		{
		case SDLK_SPACE:
			shoot();
			break;
		default:
			break;
		}
	}
}

void Player::movePlayer()
{
	SDL_PumpEvents();
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A]){
		move(Vector2(-PLAYER_SPEED, 0));
	}
	if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D]){
		move(Vector2(PLAYER_SPEED, 0));
	}
}

void Player::shoot()
{
	

	switch (upgradeState)
	{
	case USTATE_DEFAULT:
		Projectile::newProjectile("Data/Projectiles/projectile_0.png", Vector2(position.x + dimensions.x / 2, position.y - 20), 180.0, PLAYER_PROJECTILE_SPEED);
		EventHandler::raiseEvent(std::make_shared<AudioEvent>(SOUND_SHOOT));
		break;
	case USTATE_SPREAD_SHOT:
		Projectile::newProjectile("Data/Projectiles/projectile_0.png", Vector2(position.x + dimensions.x / 2, position.y - 20), 180.0, PLAYER_PROJECTILE_SPEED);
		Projectile::newProjectile("Data/Projectiles/projectile_0.png", Vector2(position.x + dimensions.x / 2, position.y - 20), 165.0, PLAYER_PROJECTILE_SPEED);
		Projectile::newProjectile("Data/Projectiles/projectile_0.png", Vector2(position.x + dimensions.x / 2, position.y - 20), 195.0, PLAYER_PROJECTILE_SPEED);
		EventHandler::raiseEvent(std::make_shared<AudioEvent>(SOUND_SHOOT));
		break;
	case USTATE_EXPLOSIVE_SHOT:
		if (!detonate){
			detonate = true;
			EventHandler::raiseEvent(std::make_shared<AudioEvent>(SOUND_SHOOT));
			currentExplosive = ExplosiveProjectile::newExplosiveProjectile("Data/Projectiles/projectile_0.png", Vector2(position.x + dimensions.x / 2, position.y - 20), 180.0, PLAYER_PROJECTILE_SPEED);
		}
		else{
			if (!currentExplosive.expired()){
				currentExplosive.lock()->detonate();
			}
			detonate = false;
		}
		break;
	default:
		break;
	}
}

void Player::setUpgradeState(UpgradeState state)
{
	upgradeState = state;
}