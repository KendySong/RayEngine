#include "Input.hpp"
#include "../Settings.hpp"

RE::Input RE::Input::s_instance;

RE::Input& RE::Input::instance()
{
	return s_instance;
}

//Default keys definition
RE::Input::Input()
{
	navigation.down[KEY_ESCAPE] = []() -> void {
		Settings::editMode = !Settings::editMode;
		if (Settings::editMode)
		{
			EnableCursor();
		}
		else
		{
			DisableCursor();
		}
	};
}

void RE::Input::executeNavigation()
{
	executeKeyEvent(this->navigation);
}

void RE::Input::executeViewDrag2D()
{
	executeKeyEvent(this->viewDrag2D);
}

void RE::Input::executeViewFPS()
{
	executeKeyEvent(this->viewFPS);
}

void RE::Input::executeKeyEvent(const RE::KeyEvent& keyEvent)
{
	for (const auto& [key, f] : keyEvent.down)
	{
		if (IsKeyPressed(key) || IsMouseButtonPressed(key))
		{
			f();
		}
	}

	for (const auto& [key, f] : keyEvent.hold)
	{
		if (IsKeyDown(key) || IsMouseButtonDown(key))
		{
			f();
		}
	}

	for (const auto& [key, f] : keyEvent.up)
	{
		if (IsKeyUp(key) || IsMouseButtonUp(key))
		{
			f();
		}
	}
}