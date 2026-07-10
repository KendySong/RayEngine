#pragma once
#include <cstdint>

#include <Raylib/raylib.h>
#include <Raylib/raymath.h>

#include <box3d/box3d.h>

class Settings
{
public :
    static Settings instance;

    static const std::uint32_t width;
    static const std::uint32_t height;

    //Camera and controls
    static const float d_zoomScale;
    static const float d_cameraSpeed;
    static const float d_sensitivity;
    static const float d_observationDist;
    static const float d_fov;
    static bool  editMode;

    static const float d_animSpeed;

    //Physics
    static const b3Vec3 g;
    static const int subStepCount;

private :
    Settings();
};