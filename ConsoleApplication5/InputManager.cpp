#include "InputManager.h"


void InputManager::setWindow(Window* _window) {
	window = _window;
}

void InputManager::checkWindowEvents(std::vector<Object>& objects) {
	sf::Event windowEvent;
	while (window->getWindow().pollEvent(windowEvent)) { // обработка ивентов
		for (unsigned int i = 0; i < objects.size(); i++) {
			objects[i].updateState(windowEvent, sf::Mouse::getPosition(window->getWindow()).x, sf::Mouse::getPosition(window->getWindow()).y);
		}
	}
}

