#include "InputManager.h"


void InputManager::setWindow(Window* _window) {
	window = _window;
}

void InputManager::checkWindowEvents() {
	sf::Event windowEvent;
	while (window->getWindow().pollEvent(windowEvent)) { // обработка ивентов
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
			Components::cam.updateMouseMovement(sf::Mouse::getPosition(window->getWindow()).x, sf::Mouse::getPosition(window->getWindow()).y);
			break;
		default:
			break;

		}
	}
}

