#include "SceneSkeleton.hpp"
#include "../../Settings.hpp"

RE::SceneSkeleton::SceneSkeleton()
{
	b3WorldDef worldDef = b3DefaultWorldDef();
	worldDef.gravity = Settings::g;
	world = b3CreateWorld(&worldDef);
}