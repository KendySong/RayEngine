#pragma once

#include <raylib/raylib.h>
#include <raylib/raymath.h>

#include <box3d/box3d.h>

#include "Transform.hpp"

namespace RE
{
    class GameObject
    {
    public:
        GameObject();
        GameObject(const b3WorldId& world, const Transform& transform, b3BodyType type);
        GameObject(const b3WorldId& world, const b3Vec3& position, const b3Quat& rotation, b3BodyType type);
        void loadModel(Model* model, const b3ShapeDef& def);
        void loadModel(Model* model, const b3ShapeDef& def, const b3Vec3& box);
        void setType(b3BodyType type);
        void updatePhysics();
        void updatePosition(const b3Vec3& position);
        
        void move(const b3Vec3& offset);
        void rotate(const b3Vec3& angle);

        void setShader(const Shader& shader);
        void draw();
        void drawWires();
        void gui();

        Model* model;
        RE::Transform transform;
       
        b3BodyType type;
        b3BodyId id;
        b3HullData* hull;


    private:
        void updateTransform();
    
        b3Vec3 m_euler;

        b3BodyDef m_bodyDef;
        bool m_enabled;     
    };
}