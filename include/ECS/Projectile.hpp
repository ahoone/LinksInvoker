#pragma once

#include "Entity.hpp"
#include "Components.hpp"
#include "../Game.hpp"
#include "../Camera.hpp"

class ProjectileComponent : public Component
{

public:

	ProjectileComponent(int rng, int sp) : _range(rng), _speed(sp)
	{}
	~ProjectileComponent();

	void init() override
	{
		_transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		_distance += _speed;

		if(_distance > _range)
		{
			entity->destroy();
		}
		//if you want to delete the projectile if it leaves the camera
		// else if(
		// 	_transform->position.x() > Game::camera->GetViewBox().x + Game::camera->GetViewBox().w ||
		// 	_transform->position.x() < Game::camera->GetViewBox().x ||
		// 	_transform->position.y() > Game::camera->GetViewBox().y + Game::camera->GetViewBox().h ||
		// 	_transform->position.y() < Game::camera->GetViewBox().y
		// 	)
		// {
		// 	entity->destroy();
		// }
	}


private:

	TransformComponent* _transform;

	int _range = 0;
	int _speed = 0;
	int _distance = 0;


};