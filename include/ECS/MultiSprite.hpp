#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

#include "Sprite.hpp"
#include "Animation.hpp"
#include "../Game.hpp"
#include "../AssetManager.hpp"

class MultiSpriteComponent : public SpriteComponent
{

public:

	// MultiSpriteComponent(const char* path)
	// {
	// 	setText(path);

	// 	_animated = true;

	// 	Animation idle = Animation(0, 2, 100);
	// 	Animation walk = Animation(1, 2, 200);

	// 	_animations.emplace("Idle", idle);
	// 	_animations.emplace("Walk", walk);

	// 	Play("Idle");
	// }

	MultiSpriteComponent(const char* id)
	{
		_texture = Game::assets->GetTexture(id);

		_animated = true;

		Animation idle = Animation(0, 2, 100);
		Animation walk = Animation(1, 2, 200);

		_animations.emplace("Idle", idle);
		_animations.emplace("Walk", walk);

		Play("Idle");
	}

	MultiSpriteComponent(SDL_Texture* texture)
	{
		_texture = texture;

		_animated = true;

		Animation idle = Animation(0, 2, 100);
		Animation walk = Animation(1, 2, 200);

		_animations.emplace("Idle", idle);
		_animations.emplace("Walk", walk);

		Play("Idle");
	}

	void update() override
	{
		if(_animated)
		{
			_srcRect.x = _srcRect.w * static_cast<int>((SDL_GetTicks() / _speed) % _frames);
		}

		_srcRect.y = _animIndex * _position->height;

		_destRect.x = static_cast<int>(_position->x());
		_destRect.y = static_cast<int>(_position->y());

		_destRect.w = _position->width * _position->scale;
		_destRect.h = _position->height * _position->scale;
	}

	void Play(const char* animName)
	{
		_frames = _animations[animName].frames;
		_animIndex = _animations[animName].index;
		_speed = _animations[animName].speed;
	}

private:

	bool _animated = false;
	int _frames = 0;
	int _speed = 100;

	int _animIndex = 0;
	std::map<const char*, Animation> _animations;

};