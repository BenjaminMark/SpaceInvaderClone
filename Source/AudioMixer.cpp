#include "AudioMixer.h"
#include "AudioEvent.h"
#include "SpaceEventType.h"
#include "EventHandler.h"


AudioMixer::AudioMixer() :GameObject(LAYER_BACKGROUND), shot(nullptr), enemyKill(nullptr), explosion(nullptr)
{
	shot = Mix_LoadWAV("Data/Audio/shoot.wav");
	enemyKill = Mix_LoadWAV("Data/Audio/invaderkilled.wav");
	explosion = Mix_LoadWAV("Data/Audio/explosion.wav");
	Mix_VolumeChunk(enemyKill, 20);
	Mix_VolumeChunk(shot, 20);
	Mix_VolumeChunk(explosion, 20);

	if (shot == nullptr || enemyKill == nullptr || explosion == nullptr){
		printf("Error loading sound effects: %s\n", Mix_GetError);
	}
}


AudioMixer::~AudioMixer()
{
	Mix_FreeChunk(shot);
	Mix_FreeChunk(enemyKill);
	Mix_FreeChunk(explosion);
}


std::weak_ptr<AudioMixer> AudioMixer::newAudioMixer()
{
	std::shared_ptr<AudioMixer> object = std::make_shared<AudioMixer>();
	GameObject::registerObject(object);
	EventHandler::registerObserver(std::weak_ptr<GameObject>(object), EVENT_AUDIO);

	return std::weak_ptr<AudioMixer>(object);
}

void AudioMixer::update()
{
	while (!eventQueue.empty()){
		auto curEvent = eventQueue.front();
		eventQueue.pop();

		if (curEvent->type == EVENT_AUDIO){
			std::shared_ptr<AudioEvent> audioEvent = std::dynamic_pointer_cast<AudioEvent>(curEvent);
			
			switch (audioEvent->type)
			{
			case SOUND_SHOOT:
				Mix_PlayChannel(-1, shot, 0);
				break;
			case SOUND_ENEMYDEATH:
				Mix_PlayChannel(-1, enemyKill, 0);
				break;
			case SOUND_EXPLOSION:
				Mix_PlayChannel(-1, explosion, 0);
				break;
			default:
				break;
			}
		}
	}
}