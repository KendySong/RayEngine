#include "Core/Window.hpp"

#define RAYGUI_IMPLEMENTATION
#include <Raylib/raygui.h>

#define RLIGHTS_IMPLEMENTATION
#include <Raylib/rlights.h>

int main()
{
    Window::instance().run();
}