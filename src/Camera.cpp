#include "Camera.hpp"

Camera* Camera::_instance = nullptr;

Camera::Camera(TransformComponent* target)
{
	//Check that we didn't already declare a camera
	if(_instance != nullptr)
	{
		_instance = this;
	}

	_viewBox.w = Game::CAMERA_WIDTH;
	_viewBox.h = Game::CAMERA_HEIGHT;

	SetTarget(target);
	update();
}

void Camera::update()
{

	if(_target != nullptr)
	{
		//Divide by 2 cause we want the target in the middle of the screen
		_viewBox.x = _target->x() + _target->width - static_cast<int>(Game::CAMERA_WIDTH / 2);
		_viewBox.y = _target->y() + _target->height - static_cast<int>(Game::CAMERA_HEIGHT / 2);

		//Check that the camera is still on the renderer
		//(actually we consider the screen as the all renderer)

		if(_viewBox.x < 0)
		{
			_viewBox.x = 0;
		}
		else if(_viewBox.x + _viewBox.w > Game::SCREEN_WIDTH)
		{
			_viewBox.x = Game::SCREEN_WIDTH - _viewBox.w;
		}

		if(_viewBox.y < 0)
		{
			_viewBox.y = 0;
		}
		else if(_viewBox.y + _viewBox.h > Game::SCREEN_HEIGHT)
		{
			_viewBox.y = Game::SCREEN_HEIGHT - _viewBox.h;
		}

		// std::cout << "x :" << _viewBox.x << std::endl;
		// std::cout << "y :" << _viewBox.y << std::endl;

		_position = Vector(_viewBox.x, _viewBox.y);
	}

}