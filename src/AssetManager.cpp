#include "AssetManager.hpp"
#include "ECS/Components.hpp"

AssetManager::AssetManager(Manager* man) : _manager(man)
{

}

AssetManager::~AssetManager()
{

}

void AssetManager::CreateProjectile(Vector pos, int range, int speed, Vector velocity, std::string id)
{
	auto& projectile(_manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x(), pos.y(), 32, 32, 1);
	projectile.addComponent<SpriteComponent>(id);
	projectile.addComponent<ProjectileComponent>(range, speed, velocity);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectile);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	_textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return _textures[id];
}