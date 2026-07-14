#pragma once
#include <box3d/box3d.h>
#include "../Core/Math.hpp"

namespace RE
{
    struct Transform
    {
    public :
        Transform();
        Transform(b3Vec3 position, b3Quat rotation, b3Vec3 scale);

        b3Vec3 position;
        b3Quat rotation;
        b3Vec3 scale; 
    };

    static const Transform transform_default = { {0,0,0}, {0,0,0,1}, {1,1,1} };
};