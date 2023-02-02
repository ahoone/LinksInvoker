#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Vector.hpp"
#include "Game.hpp"
#include "ECS/Transform.hpp"

class Camera
{

public:

	Camera()
	{
		//Check that we didn't already declare a camera
		if(_instance != nullptr)
		{
			_viewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
			_instance = this;
		}
	}

	void Update(float dt);

	SDL_Rect GetViewBox() {return _viewBox; }
	Vector GetPosition() {return _position; }
	Camera* GetInstance() {return _instance; }
	void SetTarget(TransformComponent* target) {_target = target; }

private:

	TransformComponent* _target;
	Vector _position;
	SDL_Rect _viewBox;

	static Camera* _instance;

};