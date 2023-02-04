#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Game.hpp"
#include "Entity.hpp"
#include "Components.hpp"
#include "Sprite.hpp"
#include "MultiSprite.hpp"
#include "Animation.hpp"

class Keyboard : public Component
{

public:

	TransformComponent* transform;

	MultiSpriteComponent* multiSprite;

	Keyboard() = default;
	Keyboard(SDL_Keycode up, SDL_Keycode down, SDL_Keycode left, SDL_Keycode right)
	{
		_up = up;
		_down = down;
		_left = left;
		_right = right;
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		multiSprite = &entity->getComponent<MultiSpriteComponent>();
	}

	void update() override
	{
		if(Game::event.type == SDL_KEYDOWN)
		{
			if(Game::event.key.keysym.sym == _up)
			{
				transform->velocity.y(-1);
				multiSprite->Play("Walk");
			}

			if(Game::event.key.keysym.sym == _down)
			{
				transform->velocity.y(1);
				multiSprite->Play("Walk");
			}

			if(Game::event.key.keysym.sym == _left)
			{
				transform->velocity.x(-1);
				multiSprite->Play("Walk");
			}

			if(Game::event.key.keysym.sym == _right)
			{
				transform->velocity.x(1);
				multiSprite->Play("Walk");
			}

			if(Game::event.key.keysym.sym == SDLK_SPACE)
			{
				Game::assets->CreateProjectile(Vector(100,100), 400, 2, Vector(1, 0), "ball");
				count++;
				std::cout << count << std::endl;
			}

		}

		if(Game::event.type == SDL_KEYUP)
		{
			if(Game::event.key.keysym.sym == _up)
			{
				transform->velocity.y(0);
				multiSprite->Play("Idle");
			}

			if(Game::event.key.keysym.sym == _down)
			{
				transform->velocity.y(0);
				multiSprite->Play("Idle");
			}

			if(Game::event.key.keysym.sym == _left)
			{
				transform->velocity.x(0);
				multiSprite->Play("Idle");
			}

			if(Game::event.key.keysym.sym == _right)
			{
				transform->velocity.x(0);
				multiSprite->Play("Idle");
			}

		}
	}

private:

	SDL_Keycode _up;
	SDL_Keycode _down; 
	SDL_Keycode _left; 
	SDL_Keycode _right;

	int count;

};
