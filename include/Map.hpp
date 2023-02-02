#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <fstream>
#include <iostream>

class Map
{

public:
	
	Map();
	Map(std::string path);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);

private:

};