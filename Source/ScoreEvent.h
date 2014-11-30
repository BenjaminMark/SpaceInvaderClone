#pragma once
#include "SpaceEvent.h"
class ScoreEvent : public SpaceEvent
{
public:
	int score;

	ScoreEvent(int addedScore);
	~ScoreEvent();
};

