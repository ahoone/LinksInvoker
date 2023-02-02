#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Vector.hpp"
#include "Game.hpp"
#include "ECS/Transform.hpp"

class Camera
{

public:

	Camera(TransformComponent* target);

	void update();

	SDL_Rect GetViewBox() {return _viewBox; }
	Vector GetPosition() {return _position; }
	Camera* GetInstance() {return _instance; }
	TransformComponent* GetTarget() {return _target; }
	void SetTarget(TransformComponent* target) {_target = target; }

private:

	TransformComponent* _target;
	Vector _position;
	SDL_Rect _viewBox;

	static Camera* _instance;

};