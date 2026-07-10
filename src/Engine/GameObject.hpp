#pragma once

#include <raylib/raylib.h>
#include <raylib/raymath.h>
#include "Transform.hpp"

namespace RE
{
    class GameObject
    {
    public:
        GameObject();
        void draw();
        void drawWires();
        void gui();

        Model* model;
        RE::Transform transform;

    private:
        void updateTransform();

        Vector3 m_euler;
    };
}