#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Entity.hpp"
#include "Transform.hpp"
#include "Sprite.hpp"
#include "../Game.hpp"
#include "../AssetManager.hpp"

class TileComponent : public Component
{

public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	SDL_Rect tile;
	int tileID;
	SDL_Texture* texture;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		tile.x = x;
		tile.y = y;
		tile.w = w;
		tile.h = h;
		tileID = id;

		switch(tileID)
		{
		case 0:
			texture = Game::assets->GetTexture("concrete");
			break;
		case 1:
			texture = Game::assets->GetTexture("dirt");
			break;
		case 2:
			texture = Game::assets->GetTexture("grass");
			break;
		default:
			break;
		}
	}

	void init() override
	{
		entity->addComponent<TransformComponent>((float)tile.x, (float)tile.y, (float)tile.w, (float)tile.h, 1);
		transform = &entity->getComponent<TransformComponent>();
		
		entity->addComponent<SpriteComponent>(texture);
		sprite = &entity->getComponent<SpriteComponent>();
	}


private:



};