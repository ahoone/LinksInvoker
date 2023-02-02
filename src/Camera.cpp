#include "Camera.hpp"

Camera* Camera::_instance = nullptr;

Camera::Camera(TransformComponent* target)
{
	//Check that we didn't already declare a camera
	if(_instance != nullptr)
	{
		_viewBox = {0, 0, CAMERA_WIDTH, CAMERA_HEIGHT};
		_instance = this;
	}

	SetTarget(target);
	update();
}

void Camera::update()
{

	if(_target != nullptr)
	{
		//Divide by 2 cause we want the target in the middle of the screen
		_viewBox.x = _target->x() + _target->width - CAMERA_WIDTH / 2;
		_viewBox.y = _target->y() + _target->height - CAMERA_HEIGHT / 2;

		//Check that the camera is still on the renderer

		// if(_viewBox.x < 0)
		// 	_viewBox.x = 0;

		// if(_viewBox.y < 0)
		// 	_viewBox.y = 0;

		// if(_viewBox.x + _viewBox.w > SCREEN_WIDTH)
		// 	_viewBox.x = SCREEN_WIDTH - _viewBox.w;

		// if(_viewBox.y + _viewBox.h > SCREEN_HEIGHT)
		// 	_viewBox.y = SCREEN_HEIGHT - _viewBox.h;

		_position = Vector(_viewBox.x, _viewBox.y);
	}

}