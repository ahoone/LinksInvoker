#include "Map.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"

Map::Map()
{
	LoadMap("../assets/defaultMap.txt", 36*2, 36*2);
}

Map::Map(std::string path)
{
	LoadMap(path, 36*2, 36*2);
}

Map::~Map()
{

}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	//Size of the map.txt must be equal to SizeX columns and SizeY lines
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