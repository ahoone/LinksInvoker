#include <iostream>

#include "Game.hpp"

int main(int argc, char const *argv[])
{

	//Réglage FPS
	const int FPS = 60;
	const int frameDelay = 1000/FPS;

	unsigned long int frameStart;
	int frameTime;

	Game *game = nullptr;

	game = new Game();

	//Régler ici si l'ensemble de la fenêtre de jeu se résume à
	//la caméra ou si on doit afficher par dessus un bandeau par
	//dessus (entre l'espace laissé entre les defines de 
	//SCREEN_<dir> et CAMERA_<dir>)
	game->init("LinksInvoker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);

	while(game->running())
	{

		frameStart = SDL_GetTicks();

		game->effect();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);

	}

	game->clean();

	return 0;
}