#pragma once
#include <RayEngine.hpp>

class RoomScene : public RE::SceneSkeleton
{
public :
	RoomScene();
	void update() override;
	void render() override;
	void gui() override;

private : 

};