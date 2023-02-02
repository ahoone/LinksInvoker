#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"

#include "ECS/Entity.hpp"
#include "ECS/Components.hpp"
#include "ECS/Sprite.hpp"
#include "ECS/Transform.hpp"
#include "ECS/Collider.hpp"
#include "ECS/MultiSprite.hpp"

#include "Vector.hpp"
#include "Collision.hpp"

//====================================
//=== DÉCLARATION COMPOSANTES JEUX ===
//====================================

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

Manager manager;
auto& player(manager.addEntity());

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers
};

//====================================

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
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

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if(!window)
			std::cout << "SDL_CreateWindow Error" << std::endl;
		else
			std::cout << "Window Created" << std::endl;

		renderer = SDL_CreateRenderer(window, -1, 0);
		if(!renderer)
			std::cout << "SDL_CreateRenderer Error" << std::endl;
		else
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created" << std::endl;
		}

		_running = true;
		_count = 0;

		//Load the default map.
		map = new Map();

		player.addComponent<TransformComponent>(256, 384, 32, 32, 2);
		player.addComponent<MultiSpriteComponent>("../assets/player.bmp");
		player.addComponent<Keyboard>(SDLK_z, SDLK_s, SDLK_q, SDLK_d);
		player.addComponent<ColliderComponent>("player");
		player.addGroup(groupPlayers);

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

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));

void Game::update()
{
	manager.actualize();
	manager.update();

	Vector playerVelocity = player.getComponent<TransformComponent>().velocity;
	int playerSpeed = player.getComponent<TransformComponent>().speed;

	for(auto& t : tiles)
	{
		t->getComponent<TileComponent>().tile.x = -(playerVelocity.x() * playerSpeed);
		t->getComponent<TileComponent>().tile.y = -(playerVelocity.y() * playerSpeed);
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);

	for(auto& t : tiles)
		t->draw();

	for(auto& p : players)
		p->draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "End running" << std::endl;
}

void Game::AddTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(groupMap);
}