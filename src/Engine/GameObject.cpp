#include <ImGui/rlImGui.h>
#include <Imgui/imgui.h>

#include "GameObject.hpp"
#include "SceneManager.hpp"
#include "../Core/Math.hpp"
#include "../Settings.hpp"

RE::GameObject::GameObject() : transform({ b3Vec3_zero, b3Quat_identity, b3Vec3_one }), m_enabled(true), m_euler(b3Vec3_zero)
{

}

RE::GameObject::GameObject(const b3WorldId& world, const Transform& transform, b3BodyType type) : transform(transform), m_enabled(true), m_euler(b3Vec3_zero), type(type)
{
    m_bodyDef = b3DefaultBodyDef();
    m_bodyDef.type = this->type;
    m_bodyDef.position = transform.position;
    m_bodyDef.rotation = transform.rotation;
    m_bodyDef.isEnabled = true;
    id = b3CreateBody(world, &m_bodyDef);
}

RE::GameObject::GameObject(const b3WorldId& world, const b3Vec3& position, const b3Quat& rotation, b3BodyType type) : GameObject(world, { position, rotation, {1, 1, 1} }, type)
{
    
}

void RE::GameObject::loadModel(Model* model, const b3ShapeDef& def)
{
    this->model = model;

    //Put mesh data into a points list for create a hull
    std::vector<b3Vec3> points;
    points.reserve(model->meshes[0].vertexCount);
    for (size_t i = 0; i < model->meshes[0].vertexCount; i++)
    {
        points.emplace_back(
            model->meshes[0].vertices[i * 3 + 0], 
            model->meshes[0].vertices[i * 3 + 1],
            model->meshes[0].vertices[i * 3 + 2]
            );
    }

    //Dont work if volume is 0
    hull = b3CreateHull(points.data(), points.size(), Settings::maxHullVertexCount);
    b3CreateHullShape(id, &def, hull);

    this->updatePhysics();
}

void RE::GameObject::loadModel(Model* model, const b3ShapeDef& def, const b3Vec3& box)
{
    this->model = model;
   
    b3Vec3 hbox = box * 0.5;
    b3BoxHull boxHull = b3MakeBoxHull(hbox.x, hbox.y, hbox.z);
    b3CreateHullShape(id, &def, &boxHull.base);
}

void RE::GameObject::setType(b3BodyType type)
{
    b3Body_SetType(id, type);
}

void RE::GameObject::updatePhysics()
{
    transform.position = b3Body_GetPosition(id);
    transform.rotation = b3Body_GetRotation(id);
}

void RE::GameObject::updatePosition(const b3Vec3& position)
{     
    transform.position = position;
    b3Body_SetTransform(id, position, this->transform.rotation);
}

void RE::GameObject::move(const b3Vec3& offset)
{
    transform.position += offset;
    b3Body_SetTransform(id, transform.position, this->transform.rotation);
}

void RE::GameObject::rotate(const b3Vec3& angle)
{
    b3Quat rotation = b3MakeQuatFromAxisAngle(b3Vec3_axisX, angle.x) * b3MakeQuatFromAxisAngle(b3Vec3_axisY, angle.y) * b3MakeQuatFromAxisAngle(b3Vec3_axisZ, angle.z);
    transform.rotation = rotation;
    b3Body_SetTransform(id, transform.position, rotation);
}

void RE::GameObject::setShader(const Shader& shader)
{
    model->materials[0].shader = shader;
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
    if (ImGui::DragFloat3("Position", &transform.position.x, 0.1))
    {
        this->updatePosition(transform.position);
    }

    if (ImGui::DragFloat3("Rotation", &m_euler.x, 0.01))
    {   
        this->rotate(m_euler);
    }

    ImGui::DragFloat3("Scale", &transform.scale.x, 0.01);  

    if (ImGui::Checkbox("Enabled", &m_enabled))
    {
        if (m_enabled)
        {
            b3Body_Enable(id);
        }
        else
        {
            b3Body_Disable(id);
        }
    }
}
