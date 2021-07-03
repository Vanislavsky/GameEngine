#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"camera.h"
#include"Window.h"
#include"Components.h"
#include"Object.h"

class InputManager
{
public:
	void setWindow(Window*);
	void checkWindowEvents(std::vector<Object>& objects);
private:
	Window* window;
};