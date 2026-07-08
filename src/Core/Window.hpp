#pragma once
#include <Raylib/raylib.h>
#include <Raylib/raymath.h>
#include <Raylib/rlgl.h>

#include <ImGui/rlImGui.h>
#include <Imgui/imgui.h>

#include "DefaultScene.hpp"
#include "../Game/Scenes/RoomScene.hpp"
#include "../Engine/SceneManager.hpp"

class Window
{
public :
	static Window& instance();
	void run();

private :
	static Window s_window;
	Window();	
};