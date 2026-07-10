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

#include "View.hpp"
#include "Math.hpp"
#include "../Engine/Light.hpp"


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


	GameObject m_cube1;
	GameObject m_cube2;
	GameObject m_ground;

	//Physics
	b3WorldId m_worldID;
	b3BodyId  m_bodyID1;
	b3BodyId  m_bodyID2;
	b3BodyId  m_groundID;
};