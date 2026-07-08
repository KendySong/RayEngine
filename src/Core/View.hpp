#pragma once
#include "ViewMode.hpp"

#include <Raylib/raylib.h>
#include <Raylib/rlgl.h>
#include <Raylib/raymath.h>
#include <Imgui/imgui.h>

class View
{
public :
	View() = default;
	View(ViewMode mode);
	void update();
	void gui();
	void setCurrentCamera();

	ViewMode mode;

	Camera2D camera2D;
	Camera3D camera3D;

private :
	void updateDirection();
	void updateOrbital();
	void setupDefaultInput(ViewMode mode);

	float m_zoomScale;
	float m_sensitivity;

	float m_yaw;
	float m_pitch;
	float m_speed;

	Vector3 m_direction;

	//Orbital camera
	float m_observationDist;
};