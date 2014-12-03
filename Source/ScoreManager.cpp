#include "ScoreManager.h"
#include "ScoreEvent.h"
#include "EventHandler.h"
#include "Constants.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Player.h"


ScoreManager::ScoreManager() : GameObject(LAYER_TEXT), score(1400), textcolour({ 255, 255, 255 }), currentLives(PLAYER_START_LIVES)
{
	loadHighscore();
	scoreTexture = std::make_unique<Texture>();
	highscoreTexture = std::make_unique<Texture>();
	livesTexture = std::make_unique<Texture>();
}


ScoreManager::~ScoreManager()
{
	std::ofstream highscoreFile;
	highscoreFile.open("Data/highscore.txt", std::ios::out | std::ios::trunc);
	highscoreFile << std::to_string(highscore);
	highscoreFile.close();
}

std::weak_ptr<ScoreManager> ScoreManager::newScoreCounter()
{
	std::shared_ptr<ScoreManager> object = std::make_shared<ScoreManager>();
	GameObject::registerObject(object);
	EventHandler::registerObserver(object, EVENT_SCORE);

	return std::weak_ptr<ScoreManager>(object);
}


void ScoreManager::update()
{
	if (score > highscore){
		highscore = score;
	}

	if (currentLives < 0){
		EventHandler::raiseEvent(std::make_shared<SpaceEvent>(EVENT_GAMEOVER));
	}

	//Could add a stacking bonus for how many enemies are killed with 1 hit
	while (!eventQueue.empty()){
		auto curEvent = eventQueue.front();
		eventQueue.pop();

		if (curEvent->type == EVENT_SCORE){
			auto scoreEvent = std::dynamic_pointer_cast<ScoreEvent>(curEvent);
			if (scoreEvent->lifeLost){
				currentLives--;
			}
			else {
				score += scoreEvent->score;
			}
		}
	}

	if (score >= PLAYER_UPGRADE_TWO){
		Player::setUpgradeState(USTATE_EXPLOSIVE_SHOT);
	} 
	else if (score >= PLAYER_UPGRADE_ONE){
		Player::setUpgradeState(USTATE_SPREAD_SHOT);
	}

	scoreTexture->loadText("Score: " + std::to_string(score), textcolour);
	highscoreTexture->loadText("Hi-Score: " + std::to_string(highscore), textcolour);
	livesTexture->loadText("Lives : " + std::to_string(currentLives), textcolour);
}

void ScoreManager::render()
{
	scoreTexture->render(Vector2(scoreTexture->width(), 0));
	highscoreTexture->render(Vector2(WINDOW_WIDTH / 2 - highscoreTexture->width()/2, 0));
	livesTexture->render(Vector2(WINDOW_WIDTH - livesTexture->width()*2, 0));
}

void ScoreManager::loadHighscore()
{
	std::ifstream highscoreFile("Data/highscore.txt");
	if (highscoreFile.is_open()){
		char buf[256];
		highscoreFile.getline(buf, 256);
		highscore = std::stoi(std::string(buf));
	}
	else {
		highscore = 0;
	}
}