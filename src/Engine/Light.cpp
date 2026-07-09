#include <ImGui/rlImGui.h>
#include <Imgui/imgui.h>

#include "Light.hpp"

Light::Light(const char* vsPath, const char* fsPath) : color({ 1, 1, 1 }), position({ 0, 0, 0 })
{
	shader = LoadShader(vsPath, fsPath);
	shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");

	u_color = GetShaderLocation(shader, "color");
	u_position = GetShaderLocation(shader, "lightPosition");
}

void Light::updateUniform()
{
	SetShaderValue(shader, u_color, &color, SHADER_UNIFORM_VEC3);
	SetShaderValue(shader, u_position, &position, SHADER_UNIFORM_VEC3);
}

void Light::gui()
{
	ImGui::ColorEdit3("Color", &color.x);
	ImGui::DragFloat3("Light Position", &position.x, 0.01);
}