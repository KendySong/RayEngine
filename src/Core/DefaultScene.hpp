#pragma once
#include <cstdint>
#include <vector>

#include <Raylib/raylib.h>
#include <Raylib/raymath.h>
#include <Raylib/rlgl.h>
#include <Raylib/raygui.h>

#include <ImGui/rlImGui.h>
#include <Imgui/imgui.h>

#include "View.hpp"
#include "../Engine/GameObject.hpp"
#include "../Engine/AssetManager.hpp"
#include "../Engine/Light.hpp"
#include "../Engine/Input.hpp"
#include "../Engine/Model/SceneSkeleton.hpp"

class DefaultScene : public SceneSkeleton
{
public :
	DefaultScene();

	void update() override;
	void gui() override;
	void render() override;

private :
	View m_view;
	AssetManager& m_assetManager;

	GameObject m_castle;
	GameObject m_robot;
	GameObject m_turret;
};