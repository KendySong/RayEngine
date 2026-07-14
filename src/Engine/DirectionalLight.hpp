#pragma once
#include <cstdint>

#include <Raylib/raylib.h>
#include <Raylib/rlgl.h>
#include <Raylib/rlights.h>

#include <ImGui/rlImGui.h>
#include <Imgui/imgui.h>

#include "Model/ShaderSkeleton.hpp"

namespace RE
{
	class DirectionalLight : public RE::ShaderSkeleton
	{
	public:
		DirectionalLight() = default;
		DirectionalLight(const char* vsPath, const char* fsPath, Vector3 position, Vector3 target, Color color = WHITE);

		void updateUniform() override;
		void gui() override;
		void draw();

		Light light;
		Vector3 color;
	};
}
