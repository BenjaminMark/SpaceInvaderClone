#pragma once

#include "GameObject.h"
#include <memory>

class ScoreManager : public GameObject
{
public:
	ScoreManager();
	virtual ~ScoreManager();

	static std::weak_ptr<ScoreManager> newScoreCounter();
	
	virtual void update();
	virtual void render();

protected:
	int score, highscore, currentLives;
	SDL_Colour textcolour;

	std::unique_ptr<Texture> scoreTexture;
	std::unique_ptr<Texture> highscoreTexture;
	std::unique_ptr<Texture> livesTexture;

	void loadHighscore();
};

