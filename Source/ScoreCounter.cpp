#include "ScoreCounter.h"
#include "ScoreEvent.h"
#include "EventHandler.h"


ScoreCounter::ScoreCounter() : GameObject(LAYER_TEXT), score(0), textcolour({255, 255, 255})
{
	loadHighscore();
}


ScoreCounter::~ScoreCounter()
{
}

void ScoreCounter::newScoreCounter()
{
	auto object = std::make_shared<ScoreCounter>();
	GameObject::registerObject(object);
	EventHandler::registerObserver(object, EVENT_SCORE);
}


void ScoreCounter::update()
{
	//Could add a stacking bonus for how many enemies are killed with 1 hit
	while (!eventQueue.empty()){
		auto curEvent = eventQueue.front();
		eventQueue.pop();

		if (curEvent->type == EVENT_SCORE){
			score += std::dynamic_pointer_cast<ScoreEvent>(curEvent)->score;
		}
	}

	texture->loadText("Score: " + std::to_string(score), textcolour);
}


void ScoreCounter::loadHighscore()
{
	highscore = 0;
}