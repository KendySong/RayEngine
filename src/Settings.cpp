#include "settings.hpp"

Settings Settings::instance;

Settings::Settings()
{

}

const std::uint32_t Settings::width				= 1600;
const std::uint32_t Settings::height			= 900;

//Camera and controls
const float			Settings::d_zoomScale		= 1.2;
const float			Settings::d_cameraSpeed		= 10;
const float			Settings::d_sensitivity		= 0.125;
const float			Settings::d_observationDist = 20;
const float			Settings::d_fov				= 90;
bool				Settings::editMode			= false;

const float			Settings::d_animSpeed		= 100;