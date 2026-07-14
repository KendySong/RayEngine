#include "DirectionalLight.hpp"


RE::DirectionalLight::DirectionalLight(const char* vsPath, const char* fsPath, Vector3 position, Vector3 target, Color color)
{
	shader = LoadShader(vsPath, fsPath);
	light = CreateLight(LIGHT_DIRECTIONAL, position, target, color, shader);
	this->color = { (float)color.r / 255, (float)color.g / 255, (float)color.b / 255 };
}

void RE::DirectionalLight::updateUniform()
{
	light.color = { (std::uint8_t)(color.x * 255), (std::uint8_t)(color.y * 255), (std::uint8_t)(color.z * 255) };
	UpdateLightValues(shader, light);
}

void RE::DirectionalLight::gui()
{
	ImGui::DragFloat3("Position", &light.position.x, 0.1f);
	ImGui::DragFloat3("Target", &light.target.x, 0.1f);
	ImGui::ColorEdit3("Color", &color.x);
}

void RE::DirectionalLight::draw()
{
	DrawLine3D(light.position, light.target, RED);
}