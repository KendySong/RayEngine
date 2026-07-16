#include "SceneManager.hpp"

RE::SceneManager RE::SceneManager::s_instance;

RE::SceneManager::SceneManager()
{
	currentName = "";
}

RE::SceneManager& RE::SceneManager::instance()
{
	return s_instance;
}

void RE::SceneManager::setCurrent(std::string sceneName)
{
	this->current = scenes.at(sceneName);
	currentName = sceneName;
}