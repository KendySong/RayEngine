#pragma once

namespace RE
{
	class SceneSkeleton
	{
	public:
		SceneSkeleton() = default;

		virtual void update() = 0;
		virtual void gui() = 0;
		virtual void render() = 0;

	private:
	};
}
