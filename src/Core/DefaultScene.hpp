#pragma once
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
#include "../Engine/Light.hpp"


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
	RE::GameObject m_ground;

	//Physics
	b3WorldId m_worldID;
	b3BodyId  m_bodyID1;
	b3BodyId  m_bodyID2;
	b3BodyId  m_groundID;
};