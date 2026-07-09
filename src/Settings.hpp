#pragma once
#include <cstdint>

#include <Raylib/raylib.h>
#include <Raylib/raymath.h>

class Settings
{
public :
    static Settings instance;

    static const std::uint32_t width;
    static const std::uint32_t height;
    static const float cameraSpeed;
    static bool  editMode;

    static const float defaultAnimSpeed;

private :
    Settings();
};