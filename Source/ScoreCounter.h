#pragma once

#include "GameObject.h"

class ScoreCounter : public GameObject
{
public:
	ScoreCounter();
	virtual ~ScoreCounter();

	static void newScoreCounter();
	
	virtual void update();

protected:
	int score, highscore;

	void loadHighscore();
};

