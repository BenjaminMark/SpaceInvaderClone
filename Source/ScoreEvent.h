#pragma once
#include "SpaceEvent.h"
class ScoreEvent : public SpaceEvent
{
public:
	const bool lifeLost;
	const int score;

	ScoreEvent(bool lifeLost, int addedScore);
	~ScoreEvent();
};

