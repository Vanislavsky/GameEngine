#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"camera.h"
#include"Window.h"
#include"Components.h"

class InputManager
{
public:
	void setWindow(Window*);
	void checkWindowEvents();
private:
	Window* window;
};