#include "Transform.hpp"

RE::Transform::Transform() : position({ 0, 0, 0 }), rotation(b3Quat_identity), scale({ 1, 1, 1 })
{
    
}

RE::Transform::Transform(b3Vec3 position, b3Quat rotation, b3Vec3 scale) : position(position), rotation(rotation), scale(scale)
{
    
}