#include "GameObject.hpp"

#include <ImGui/rlImGui.h>
#include <Imgui/imgui.h>

RE::GameObject::GameObject()
{
    isStatic = false;
    transform.position      = b3Vec3_zero;
    transform.rotation      = b3Quat_identity;
    transform.scale         = b3Vec3_one;
    
    m_euler = Vector3(0);
}

void RE::GameObject::updatePhysics()
{
    if (isStatic)
    {
        this->transform.position = b3Body_GetPosition(id);
        this->transform.rotation = b3Body_GetRotation(id);
    }
}

void setBodyType()
{

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
    if (ImGui::DragFloat3("Rotation", &m_euler.x, 0.01))
    {   
        transform.rotation = b3MakeQuatFromAxisAngle(b3Vec3_axisX, m_euler.x) * b3MakeQuatFromAxisAngle(b3Vec3_axisY, m_euler.y) * b3MakeQuatFromAxisAngle(b3Vec3_axisZ, m_euler.z);
    }
    ImGui::DragFloat3("Scale", &transform.scale.x, 0.01);  
}
