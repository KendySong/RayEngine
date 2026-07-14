#pragma once
#include <string>
#include <unordered_map>

#include <box3d/box3d.h>

#include "Model/SceneSkeleton.hpp"

namespace RE
{
	class SceneManager
	{
	public:
		static SceneManager& instance();
		void setCurrent(std::string sceneName);

		std::unordered_map<std::string, SceneSkeleton*> scenes;
		SceneSkeleton* current;

	private:
		SceneManager() = default;
		static SceneManager s_instance;
	};
}
