#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"camera.h"
#include"Window.h"

class InputManager
{
public:
	void setWindow(Window*);
	void setCamera(camera* _cam);
	void checkWindowEvents();
private:
	Window* window;
	camera* cam;
};