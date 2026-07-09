#include "Core/Window.hpp"

#define RAYGUI_IMPLEMENTATION
#include <Raylib/raygui.h>

int main()
{
    Window::instance().run();
}