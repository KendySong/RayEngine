#pragma once
#include <string>

#include <box3d/box3d.h>

namespace RE
{
	class SceneSkeleton
	{
	public:
		SceneSkeleton();

		virtual void update() = 0;
		virtual void gui() = 0;
		virtual void render() = 0;

		b3WorldId world;

	private:
		
	};
}
