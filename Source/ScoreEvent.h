#pragma once
#include "SpaceEvent.h"
class ScoreEvent : public SpaceEvent
{
public:
	const int score;

	ScoreEvent(int addedScore);
	~ScoreEvent();
};

