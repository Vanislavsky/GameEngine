#include "Scene.h"


camera& Scene::getCamera() {
	return camera;
}

void Scene::addObject(Object obj) {
	objects.push_back(obj);
}

std::vector<Object>& Scene::getObjects() {
	return objects;
}

std::vector<LightObject>& Scene::getLightObjects() {
	return lightObjects;
}

void Scene::addLightObject(LightObject lightObj) {
	lightObjects.push_back(lightObj);
}
