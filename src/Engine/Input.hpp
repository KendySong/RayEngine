#pragma once
#include <unordered_map>
#include <functional>

#include <raylib/raylib.h>

#include "../Core/View.hpp"
#include "KeyEvent.hpp"

class Input
{
public :
	static Input& instance();
	void executeNavigation();
	void executeViewDrag2D();
	void executeViewFPS();

	//input-function binding foreach situation
	KeyEvent navigation;
	KeyEvent viewDrag2D;
	KeyEvent viewFPS;



private:
	Input();
	void executeKeyEvent(const KeyEvent& keyEvent);

	static Input s_instance;
};