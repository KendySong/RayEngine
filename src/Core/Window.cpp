#include "Window.hpp"
#include "../settings.hpp"
#include "../Engine/Input.hpp"

Window Window::s_window;

Window& Window::instance()
{
	return s_window;
}

Window::Window()
{
	InitWindow(Settings::width, Settings::height, "RayEngine");
	rlImGuiSetup(true);

	SetExitKey(KEY_NULL);
}

void Window::run()
{
	//Load scenes
	DefaultScene scene;
	RoomScene roomScene;

	RE::SceneManager& sceneManager = RE::SceneManager::instance();
	
	sceneManager.scenes["default"] = &scene;
	sceneManager.scenes["room"] = &roomScene;

	sceneManager.setCurrent("default");
	
	//Init default keys setup
	RE::Input::instance();
	while (!WindowShouldClose())
	{
		//Update
		sceneManager.current->update();
		RE::Input::instance().executeNavigation();
		
		//Render
		BeginDrawing();
		sceneManager.current->render();

		//Gui
		if (Settings::editMode)
		{
			rlImGuiBegin();
			sceneManager.current->gui();
			rlImGuiEnd();
		}
	
		EndDrawing();		
	}

	rlImGuiShutdown();
	CloseWindow();
}