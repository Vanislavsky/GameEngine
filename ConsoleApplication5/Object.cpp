#include "Object.h"


Object::Object(unsigned int _id, vec3 _position) : id(_id), position(_position) {}

unsigned int Object::getId() {
	return id;
}

void Object::setTypeObject(ObjectType _type) {
	objectType = _type;
}

ObjectType Object::getType() {
	return objectType;
}

void Object::setPosition(vec3 _position) {
	position = _position;
}

vec3 Object::getPosition() {
	return position;
}

Model* Object::getModel() {
	return model;
}

vec3* Object::getColor() {
	return colorLight;
}

void Object::addComponent(Model* _model) {
	model = _model;
}

void Object::addComponent(vec3* _colorLight) {
	colorLight = _colorLight;
}