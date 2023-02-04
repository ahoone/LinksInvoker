#pragma once

#include <map>
#include <string>

#include "TextureManager.hpp"
#include "Vector.hpp"
#include "ECS/Entity.hpp"

class AssetManager
{

public:

	AssetManager(Manager* man);
	~AssetManager();

	//*************************
	//*** CREATE PROJECTILE ***
	//*************************

	void CreateProjectile(Vector pos, int range, int speed, Vector velocity, std::string id);

	//**************************
	//*** TEXTURE MANAGEMENT ***
	//**************************

	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

private:

	Manager* _manager;
	std::map<std::string, SDL_Texture*> _textures; 

};