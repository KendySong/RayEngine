#include "AssetManager.hpp"

RE::AssetManager RE::AssetManager::s_intance;

RE::AssetManager& RE::AssetManager::instance()
{
	return s_intance;
}

void RE::AssetManager::setModeleTexture(const std::string& name, int mapType, const Texture2D& texture)
{
	SetMaterialTexture(&model[name].materials[0], mapType, texture);
}

void RE::AssetManager::setMaterialShader(const std::string& name, const Shader& shader)
{
	model[name].materials[0].shader = shader;
}