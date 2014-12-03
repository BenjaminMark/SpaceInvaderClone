#include "GameOver.h"
#include "Timer.h"
#include "Vector2.h"
#include "Constants.h"


GameOver::GameOver() : gameoverScreen(Texture::load("Data/gameOver.png"))
{
}


GameOver::~GameOver()
{
}

int GameOver::waitForPlayer()
{
	Timer timer;
	int retVal = 1;
	SDL_Event* input = new SDL_Event();

	while (retVal > 0){
		timer.start();

		while (SDL_PollEvent(input) != 0){
			if (input->type == SDL_QUIT){
				retVal = -1;
			}
			else if(input->type == SDL_KEYDOWN && input->key.keysym.sym == SDLK_RETURN){
				retVal =  0;
			}
		}
		Texture::clearRenderer();
		gameoverScreen->render(Vector2(0,0));
		Texture::presentRenderer();

		if (timer.getTicks() < TICKS_PER_FRAME){
			SDL_Delay(TICKS_PER_FRAME - timer.getTicks());
		}
	}

	delete input;
	return retVal;
}
