#pragma once
#include <Raylib/raylib.h>
#include <Raylib/rlgl.h>

#include "Model/ShaderSkeleton.hpp"

namespace RE
{
	class PointLight : public RE::ShaderSkeleton
	{
	public:
		PointLight() = default;
		PointLight(const char* vsPath, const char* fsPath, Vector3 position, Color color = WHITE);

		void updateUniform() override;
		void gui() override;

		Vector3 color;
		Vector3 position;

	private:
		int u_color;
		int u_position;
	};
}
