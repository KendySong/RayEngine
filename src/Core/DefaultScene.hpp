#pragma once
#include <string>
#include <cstdint>
#include <vector>

#include <Raylib/raylib.h>
#include <Raylib/raymath.h>
#include <Raylib/rlgl.h>
#include <Raylib/raygui.h>

#include <ImGui/rlImGui.h>
#include <Imgui/imgui.h>

#include <RayEngine.hpp>
#include <box3d/box3d.h>
#include <box3d/math_functions.h>

#include "View.hpp"
#include "Math.hpp"

class DefaultScene : public RE::SceneSkeleton
{
public :
	DefaultScene();

	void update() override;
	void gui() override;
	void render() override;

private :
	View m_view;
	RE::AssetManager& m_assetManager;
	RE::FrameBuffer m_pixelised;

	RE::GameObject m_castle;
	RE::GameObject m_robot;
	RE::GameObject m_turret;

	RE::GameObject m_cube1;
	RE::GameObject m_cube2;
	RE::GameObject m_cube3;
	RE::GameObject m_ground;
	std::vector<RE::GameObject> m_cubeGroup;

	RE::DirectionalLight* p_dlight;
	RE::PointLight* p_light;
	RE::PointLight* p_lightRed;
};