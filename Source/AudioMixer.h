#pragma once
#include <memory>
#include "GameObject.h"
#include "SDL_Mixer.h"

class AudioMixer : public GameObject
{
public:
	AudioMixer();
	~AudioMixer();

	static std::weak_ptr<AudioMixer> newAudioMixer();
	virtual void update();

private:

	Mix_Chunk* shot;
	Mix_Chunk* enemyKill;
	Mix_Chunk* explosion;
};

