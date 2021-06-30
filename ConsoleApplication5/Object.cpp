#include "Object.h"


Object::Object(string const& path, vec3 _position) : model(path), position(_position) {}

unsigned int Object::getId() {
	return id;
}

void Object::setPosition(vec3 _position) {
	position = _position;
}

vec3 Object::getPosition() {
	return position;
}

Model Object::getModel() {
	return model;
}