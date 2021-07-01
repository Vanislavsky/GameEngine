#include "Scene.h"




void Scene::addObject(Object obj) {
	objects.push_back(obj);
}

std::vector<Object>& Scene::getObjects() {
	return objects;
}

