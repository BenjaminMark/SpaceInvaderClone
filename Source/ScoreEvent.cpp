#include "ScoreEvent.h"


ScoreEvent::ScoreEvent(bool lifeLost, int addedScore) : SpaceEvent(EVENT_SCORE), score(addedScore), lifeLost(lifeLost)
{
}



ScoreEvent::~ScoreEvent()
{
}
