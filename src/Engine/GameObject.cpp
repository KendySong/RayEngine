#include "GameObject.hpp"

#include <ImGui/rlImGui.h>
#include <Imgui/imgui.h>

GameObject::GameObject()
{
    transform.translation   = { 0, 0, 0 };
    transform.rotation      = QuaternionFromEuler(0, 0, 0);
    transform.scale         = { 1, 1, 1 };
}

void GameObject::draw()
{
    Matrix translate = MatrixTranslate(transform.translation.x, transform.translation.y, transform.translation.z);
    Matrix rotation = MatrixRotateX(transform.rotation.x) * MatrixRotateY(transform.rotation.y) * MatrixRotateZ(transform.rotation.z);
    Matrix scale = MatrixScale(transform.scale.x, transform.scale.y, transform.scale.z);

    Matrix world = translate * rotation * scale;
    model->transform = world;

    DrawModel(*model, { 0, 0, 0 }, 1, WHITE);
}

void GameObject::gui()
{
    ImGui::DragFloat3("Position", &transform.translation.x, 0.1);
    ImGui::DragFloat3("Rotation", &transform.rotation.x, 0.01);
    ImGui::DragFloat3("Scale", &transform.scale.x, 0.01);
}
