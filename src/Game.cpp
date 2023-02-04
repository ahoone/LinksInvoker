#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector.hpp"
#include "Collision.hpp"
#include "Camera.hpp"
#include "AssetManager.hpp"

//====================================
//=== DÉCLARATION COMPOSANTES JEUX ===
//====================================

Map* map;

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
Camera* Game::camera = nullptr;
AssetManager* Game::assets = new AssetManager(&manager);
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& collider(manager.getGroup(Game::groupCollider));
auto& projectile(manager.getGroup(Game::groupProjectile));

//====================================

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, bool fullscreen)
{
	Uint32 flags = 0;

	//flags for window
	if(fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if(SDL_Init(SDL_INIT_EVERYTHING))
	{
		std::cout << "SDL_Init Error" << std::endl;
		_running = false;
	}
	else
	{
		std::cout << "Subsystem Initialized" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, Game::CAMERA_WIDTH, Game::CAMERA_HEIGHT, flags);
		if(!window)
			std::cout << "SDL_CreateWindow Error" << std::endl;
		else
			std::cout << "Window Created" << std::endl;

		//flags for renderer optimization
		flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

		renderer = SDL_CreateRenderer(window, -1, flags);
		if(!renderer)
			std::cout << "SDL_CreateRenderer Error" << std::endl;
		else
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created" << std::endl;
		}

		_running = true;
		_count = 0;

		//Load textures
		assets->AddTexture("concrete", "../assets/concrete.bmp");
		assets->AddTexture("dirt", "../assets/dirt.bmp");
		assets->AddTexture("grass", "../assets/grass.bmp");
		assets->AddTexture("player", "../assets/player.bmp");
		assets->AddTexture("ball", "../assets/ball.bmp");

		//Load the default map
		map = new Map();

		//Init the player
		player.addComponent<TransformComponent>(Game::CAMERA_WIDTH/2, Game::CAMERA_HEIGHT/2, 32, 32, 2);
		player.addComponent<MultiSpriteComponent>("player");
		player.addComponent<Keyboard>(SDLK_z, SDLK_s, SDLK_q, SDLK_d);
		player.addComponent<ColliderComponent>("player");
		player.addGroup(Game::groupPlayers);

		//Init the camera
		Game::camera = new Camera(&player.getComponent<TransformComponent>());

		std::cout << "Game::init ok" << std::endl;
	}
}

void Game::effect()
{
	SDL_PollEvent(&event);
	switch(event.type)
	{
		case SDL_QUIT:
			_running = false;
			break;

		default:
			break;
	}
}

void Game::update()
{
	manager.actualize();
	manager.update();
	Game::camera->update();
}

void Game::render()
{
	SDL_RenderClear(renderer);

	for(auto& t : tiles)
		t->draw();

	for(auto& p : players)
		p->draw();

	for(auto& c : collider)
		c->draw();

	for(auto& p : projectile)
		p->draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	//manager.clearEntities();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "End running" << std::endl;
}

void Game::AddTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(Game::groupMap);
}