#include "LightObject.h"

LightObject::LightObject(vec3 _color, vec3 _position) : color(_color), position(_position) {}

unsigned int LightObject::getId() {
	return id;
}

void LightObject::setPosition(vec3 _position) {
	position = _position;
}

vec3 LightObject::getPosition() {
	return position;
}

void LightObject::setColor(vec3 _color) {
	color = _color;
}

vec3 LightObject::getColor() {
	return color;
}