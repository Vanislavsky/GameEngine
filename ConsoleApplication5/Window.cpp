#include "Window.h"


Window::Window(unsigned int _width, unsigned int _height):
	settings(24, 8, 4, 3, sf::ContextSettings::Core),
	window(sf::VideoMode(_width, _height, 32), "First Window",
		sf::Style::Titlebar | sf::Style::Close, settings) {}

sf::Window& Window::getWindow() {
	return window;
}


void Window::checkWindowEvents() {
	sf::Event windowEvent;
	while (window.pollEvent(windowEvent)) { // обработка ивентов
		switch (windowEvent.type) {
		case sf::Event::KeyPressed:
			if (windowEvent.key.code == sf::Keyboard::W) {
				auto pos_add = Components::cam.get_front() * Components::cam.cameraSpeed;
				Components::cam.set_postion(Components::cam.get_position() - pos_add);
			}

			if (windowEvent.key.code == sf::Keyboard::S) {
				auto pos_min = Components::cam.get_front() * Components::cam.cameraSpeed;
				Components::cam.set_postion(Components::cam.get_position() + pos_min);

			}

			if (windowEvent.key.code == sf::Keyboard::A) {
				auto pos_min = Components::cam.get_front().vector_product(Components::cam.get_up()).normal() * Components::cam.cameraSpeed;
				Components::cam.set_postion(Components::cam.get_position() - pos_min);
			}

			if (windowEvent.key.code == sf::Keyboard::D) {
				auto pos_add = Components::cam.get_front().vector_product(Components::cam.get_up()).normal() * Components::cam.cameraSpeed;
				Components::cam.set_postion(Components::cam.get_position() + pos_add);
			}
			break;

		case sf::Event::MouseMoved:
			Components::cam.updateMouseMovement(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			break;
		default:
			break;

		}
	}
}

void Window::display() {
	window.display();
}