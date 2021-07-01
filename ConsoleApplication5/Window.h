#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"camera.h"
#include"Components.h"

class Window {
public:
	Window(unsigned int _width = 1800, unsigned int _height = 1600);


	sf::Window& getWindow();

	void checkWindowEvents();

	void display();

private:
	sf::Window window;
	sf::ContextSettings settings;
	unsigned int width;
	unsigned int height;
};

