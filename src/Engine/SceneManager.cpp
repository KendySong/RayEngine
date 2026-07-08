#include "SceneManager.hpp"

SceneManager SceneManager::s_instance;

SceneManager& SceneManager::instance()
{
	return s_instance;
}

void SceneManager::setCurrent(std::string sceneName)
{
	this->current = scenes[sceneName];
}