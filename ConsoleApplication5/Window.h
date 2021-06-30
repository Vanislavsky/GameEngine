#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"camera.h"

class Window {
public:
	Window(unsigned int _width = 1800, unsigned int _height = 1600);

	void setCamera(camera* _cam);
	void checkWindowEvents();

	void display();

private:
	sf::Window window;
	sf::ContextSettings settings;
	unsigned int width;
	unsigned int height;

	camera* cam;
};

