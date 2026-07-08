#pragma once
#include <Raylib/raylib.h>
#include <Raylib/rlgl.h>

#include "Model/ShaderSkeleton.hpp"

class Light : public ShaderSkeleton
{
public :
	Light() = default;
	Light(const char* vsPath, const char* fsPath);

	void updateUniform() override;
	void gui() override;
	
	Vector3 color;
	Vector3 position;

private : 
	int u_color;
	int u_position;
};