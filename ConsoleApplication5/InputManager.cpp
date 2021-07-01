#include "InputManager.h"


void InputManager::setWindow(Window* _window) {
	window = _window;
}

void InputManager::setCamera(camera* _cam) {
	cam = _cam;
}
void InputManager::checkWindowEvents() {
	sf::Event windowEvent;
	while (window->getWindow().pollEvent(windowEvent)) { // обработка ивентов
		switch (windowEvent.type) {
		case sf::Event::KeyPressed:
			if (windowEvent.key.code == sf::Keyboard::W) {
				auto pos_add = cam->get_front() * cam->cameraSpeed;
				cam->set_postion(cam->get_position() - pos_add);
			}

			if (windowEvent.key.code == sf::Keyboard::S) {
				auto pos_min = cam->get_front() * cam->cameraSpeed;
				cam->set_postion(cam->get_position() + pos_min);

			}

			if (windowEvent.key.code == sf::Keyboard::A) {
				auto pos_min = cam->get_front().vector_product(cam->get_up()).normal() * cam->cameraSpeed;
				cam->set_postion(cam->get_position() - pos_min);
			}

			if (windowEvent.key.code == sf::Keyboard::D) {
				auto pos_add = cam->get_front().vector_product(cam->get_up()).normal() * cam->cameraSpeed;
				cam->set_postion(cam->get_position() + pos_add);
			}
			break;

		case sf::Event::MouseMoved:
			cam->updateMouseMovement(sf::Mouse::getPosition(window->getWindow()).x, sf::Mouse::getPosition(window->getWindow()).y);
			break;
		default:
			break;

		}
	}
}

