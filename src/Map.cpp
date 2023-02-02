#include "Map.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"

Map::Map()
{
	LoadMap("../assets/defaultMap.txt", 32, 24);
}

Map::Map(std::string path)
{
	LoadMap(path, 32, 24);
}

Map::~Map()
{

}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	for(int y=0; y<sizeY; y++)
	{
		for(int x=0; x<sizeX; x++)
		{
			mapFile.get(tile);
			Game::AddTile(atoi(&tile), x*32, y*32);
			mapFile.ignore();
		}
	}

	mapFile.close();
}