#pragma once
#include <box3d/box3d.h>

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
}