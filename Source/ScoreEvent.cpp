#include "ScoreEvent.h"


ScoreEvent::ScoreEvent(int addedScore) : SpaceEvent(EVENT_SCORE), score(addedScore)
{
}


ScoreEvent::~ScoreEvent()
{
}
