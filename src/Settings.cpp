#include "settings.hpp"

Settings Settings::instance;

Settings::Settings()
{

}

const int			Settings::seed				= time(nullptr);
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

//Physics
const b3Vec3		Settings::g					= { 0, -15, 0 };
const int			Settings::subStepCount		= 4;
int					Settings::maxHullVertexCount= 32;