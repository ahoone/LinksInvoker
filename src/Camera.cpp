#include "Camera.hpp"

Camera* Camera::_instance = nullptr;

void Camera::Update(float dt)
{

	if(_target != nullptr)
	{
		//Divide by 2 cause we target the middle of the screen
		_viewBox.x = _target->x() - SCREEN_WIDTH / 2;
		_viewBox.y = _target->y() - SCREEN_HEIGHT / 2;

		//Check that the camera is still on the renderer

		if(_viewBox.x < 0)
			_viewBox.x = 0;

		if(_viewBox.y < 0)
			_viewBox.y = 0;

		if(_viewBox.x + _viewBox.w > SCREEN_WIDTH)
			_viewBox.x = SCREEN_WIDTH - _viewBox.w;

		if(_viewBox.y + _viewBox.h > SCREEN_HEIGHT)
			_viewBox.y = SCREEN_HEIGHT - _viewBox.h;

		_position = Vector(_viewBox.x, _viewBox.y);

	}

}