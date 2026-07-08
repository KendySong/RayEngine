#include "View.hpp"
#include "../Settings.hpp"
#include "../Engine/Input.hpp"
#include "Math.hpp"

View::View(ViewMode mode)
{
	this->mode = mode;
	m_zoomScale = 1.2f;
	m_sensitivity = 0.125f;
	m_observationDist = 20;
	m_yaw = 0;
	m_pitch = 0;
	m_speed = Settings::cameraSpeed;

	camera2D.target = { 0, 0 };
	camera2D.offset = { 0, 0 };
	camera2D.rotation = 0;
	camera2D.zoom = 1.0f;

	camera3D.position = { 0, 0, 0};
	camera3D.target = { 0, 0, 0 };
	camera3D.up = { 0, 1, 0 };
	camera3D.fovy = 90;
	camera3D.projection = CAMERA_PERSPECTIVE;

	this->setupDefaultInput(this->mode);
	DisableCursor();

	if (mode == ViewMode::ORBITAL)
	{
		m_yaw = 0.3;
		m_pitch = 0.7;
		updateOrbital();
	}
	else
	{
		updateDirection();
	}
	
}

void View::update() 
{
	float wheel = GetMouseWheelMove();
	Vector2 mouseDelta = GetMouseDelta() * m_sensitivity;

	//Update camera direction
	mouseDelta *= DEG2RAD;
	m_yaw += mouseDelta.x;
	m_pitch -= mouseDelta.y;
	m_pitch = Math::clamp(-ALMOST_PI_2, ALMOST_PI_2, m_pitch);
	
	switch (mode)
	{
	case ViewMode::Drag2D:	
		Input::instance().executeViewDrag2D();
		if (wheel != 0)
		{
			Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera2D);
			
			//Replace the camera
			camera2D.offset = GetMousePosition();
			camera2D.target = mouseWorldPos;
			
			camera2D.zoom = wheel > 0 ? camera2D.zoom * m_zoomScale : camera2D.zoom / m_zoomScale;
		}
		break;

	case ViewMode::FPS:
		this->updateDirection();
		Input::instance().executeViewFPS();
		camera3D.target = camera3D.position + m_direction;	
		break;

	case ViewMode::ORBITAL:
		if (wheel != 0)
		{
			m_observationDist = wheel > 0 ? m_observationDist / m_zoomScale : m_observationDist * m_zoomScale;
		}
		
		this->updateOrbital();
		camera3D.position = m_direction;
		camera3D.position *= m_observationDist;
		break;
	}
}

void View::gui()
{
	if (ImGui::TreeNode("Camera"))
	{
		ImGui::DragFloat("Sensitivity", &m_sensitivity, 0.01);
		ImGui::DragFloat("Zoom scale", &m_zoomScale);

		ImGui::SeparatorText("Camera 2D");
		ImGui::SliderFloat("Zoom", &camera2D.zoom, 0, 10);

		ImGui::SeparatorText("Camera 3D");
		ImGui::DragFloat("FOV", &camera3D.fovy);
		ImGui::DragFloat3("Position", &camera3D.position.x, 0.1);
		ImGui::DragFloat("Speed", &m_speed, 0.1);
		
		ImGui::TreePop();
	}
}

void View::setCurrentCamera()
{
	this->setupDefaultInput(this->mode);
}

void View::updateDirection()
{
	m_direction.x = cos(m_yaw) * cos(m_pitch);
	m_direction.y = sin(m_pitch);
	m_direction.z = sin(m_yaw) * cos(m_pitch);
}

void View::updateOrbital()
{
	m_direction.x = cos(m_yaw) * cos(-m_pitch);
	m_direction.y = sin(-m_pitch);
	m_direction.z = sin(m_yaw) * cos(-m_pitch);
}

void View::setupDefaultInput(ViewMode mode)
{
	switch (mode)
	{
	case ViewMode::Drag2D:
		Input::instance().viewDrag2D.hold[MOUSE_BUTTON_RIGHT] = [&]() ->void {
			Vector2 mouseDelta = GetMouseDelta() * m_sensitivity;
			camera2D.target -= mouseDelta / camera2D.zoom;
		};
		break;

	case ViewMode::FPS:
		Input::instance().viewFPS.hold[KEY_W] = [&]() -> void {
			this->camera3D.position += m_direction * m_speed * GetFrameTime();
		};

		Input::instance().viewFPS.hold[KEY_S] = [&]() -> void {
			camera3D.position -= m_direction * m_speed * GetFrameTime();
		};

		Input::instance().viewFPS.hold[KEY_A] = [&]() -> void {
			camera3D.position += Math::normalize(Math::cross(camera3D.up, m_direction)) * m_speed * GetFrameTime();
		};

		Input::instance().viewFPS.hold[KEY_D] = [&]() -> void {
			camera3D.position -= Math::normalize(Math::cross(camera3D.up, m_direction)) * m_speed * GetFrameTime();
		};

		Input::instance().viewFPS.hold[KEY_SPACE] = [&]() -> void {
			camera3D.position.y += m_speed * GetFrameTime();
		};

		Input::instance().viewFPS.hold[KEY_LEFT_SHIFT] = [&]() -> void {
			camera3D.position.y -= m_speed * GetFrameTime();
		};
		break;
	}
}