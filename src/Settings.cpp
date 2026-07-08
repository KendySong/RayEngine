#include "settings.hpp"

Settings Settings::instance;

Settings::Settings()
{

}

const std::uint32_t Settings::width			= 1600;
const std::uint32_t Settings::height		= 900;
const float			Settings::cameraSpeed	= 10;
bool				Settings::editMode		= false;