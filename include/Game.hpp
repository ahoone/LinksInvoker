#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>

class ColliderComponent;
class Camera;
class AssetManager;

class Game
{

public:
	Game();
	~Game();

	//**********************
	//*** INITIALISATION ***
	//**********************

	void init(const char* title, int xpos, int ypos, bool fullscreen);
	void initEntities();
	void placeWall();
	void placeGoal();

	//*********************
	//*** BOUCLE DE JEU ***
	//*********************
	
	void effect();
	void update();
	void render();
	void clean();

	bool running() {return _running; };

	//******************************
	//*** GÉRER LES INTERACTIONS ***
	//******************************

	static void AddTile(int id, int x, int y);

	static SDL_Renderer* renderer;
	static Camera* camera;
	static AssetManager* assets;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

	//********************************
	//*** TAILLE FENÊTRE ET CAMÉRA ***
	//********************************

	static const int SCREEN_WIDTH = 32*36*2; //1024;
	static const int SCREEN_HEIGHT = 32*36*2; //768;

	static const int CAMERA_WIDTH = 768; //512 //1024
	static const int CAMERA_HEIGHT = 576; //384 //768

private:
	int _count;
	bool _running;
	SDL_Window* window;
};