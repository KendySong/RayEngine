#pragma once
#include <RayEngine.hpp>

class SandboxScene : public RE::SceneSkeleton
{
public :
	SandboxScene();
	void update() override;
	void render() override;
	void gui() override;

private : 

};