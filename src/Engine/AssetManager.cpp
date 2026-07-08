#include "AssetManager.hpp"

AssetManager AssetManager::s_intance;

AssetManager& AssetManager::instance()
{
	return s_intance;
}

void AssetManager::setModeleTexture(const std::string& name, int mapType, const Texture2D& texture)
{
	SetMaterialTexture(&modele[name].materials[0], mapType, texture);
}

void AssetManager::setMaterialShader(const std::string& name, const Shader& shader)
{
	modele[name].materials[0].shader = shader;
}