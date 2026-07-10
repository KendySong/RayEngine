#pragma once
#include <raylib/raylib.h>

namespace RE
{
	class ShaderSkeleton
	{
	public:
		ShaderSkeleton() = default;
		virtual ~ShaderSkeleton();

		virtual void updateUniform();
		virtual void gui();

		Shader shader;

	private:
	};
}
