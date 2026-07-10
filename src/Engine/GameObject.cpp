#include "GameObject.hpp"

#include <ImGui/rlImGui.h>
#include <Imgui/imgui.h>

RE::GameObject::GameObject()
{
    transform.position      = { 0, 0, 0 };
    transform.rotation      = b3Quat_identity;
    transform.scale         = { 1, 1, 1 };
}

void RE::GameObject::draw()
{
    this->updateTransform();
    DrawModel(*model, { 0, 0, 0 }, 1, WHITE);
}

void RE::GameObject::drawWires()
{
    this->updateTransform();
    DrawModelWires(*model, { 0, 0, 0 }, 1, WHITE);
}

void RE::GameObject::updateTransform()
{
    Matrix translate = MatrixTranslate(transform.position.x, transform.position.y, transform.position.z);
    Matrix rotation = QuaternionToMatrix({ transform.rotation.v.x, transform.rotation.v.y, transform.rotation.v.z, transform.rotation.s });
    Matrix scale = MatrixScale(transform.scale.x, transform.scale.y, transform.scale.z);

    Matrix world = scale * rotation * translate;
    model->transform = world;
}

void RE::GameObject::gui()
{
    ImGui::DragFloat3("Position", &transform.position.x, 0.1);
    //ImGui::DragFloat3("Rotation", &transform.rotation.x, 0.01);
    ImGui::DragFloat3("Scale", &transform.scale.x, 0.01);
}
