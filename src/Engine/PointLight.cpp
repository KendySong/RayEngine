#include <ImGui/rlImGui.h>
#include <Imgui/imgui.h>

#include "PointLight.hpp"

RE::PointLight::PointLight(const char* vsPath, const char* fsPath, Vector3 position, Color color)
{
	shader = LoadShader(vsPath, fsPath);
	shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");

	this->position = position;
	this->color = { (float)color.r / 255, (float)color.g / 255, (float)color.b / 255 };

	u_color = GetShaderLocation(shader, "color");
	u_position = GetShaderLocation(shader, "lightPosition");
	this->updateUniform();
}

void RE::PointLight::updateUniform()
{
	SetShaderValue(shader, u_color, &color, SHADER_UNIFORM_VEC3);
	SetShaderValue(shader, u_position, &position, SHADER_UNIFORM_VEC3);
}

void RE::PointLight::gui()
{
	ImGui::ColorEdit3("Color", &color.x);
	ImGui::DragFloat3("Light Position", &position.x, 0.01);
}