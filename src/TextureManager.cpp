#include "TextureManager.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "Vector.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* filename)
{
	SDL_Surface* tempSurface = SDL_LoadBMP(filename);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

	// std::cout << SDL_GetError() << std::endl;
	// SDL_ClearError();

	SDL_FreeSurface(tempSurface);

	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest)
{
	Vector cam = Game::camera->GetPosition();
	SDL_Rect camRect;

	camRect.x = dest.x - cam.x();
	camRect.y = dest.y - cam.y();
	camRect.w = dest.w;
	camRect.h = dest.h;

	SDL_RenderCopy(Game::renderer, texture, &src, &camRect);
}