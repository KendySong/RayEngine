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
        void updatePhysics();
        void setBodyType();
        void draw();
        void drawWires();  
 
        void gui();

        Model* model;
        RE::Transform transform;

        bool isStatic;
        b3BodyId id;

    private:
        void updateTransform();

        
        Vector3 m_euler;
    };
}