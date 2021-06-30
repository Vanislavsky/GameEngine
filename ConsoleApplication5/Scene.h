#pragma once

#include"Object.h"
#include"LightObject.h"
#include<vector>
#include"camera.h"

class Scene
{
public:
	camera& getCamera();
	std::vector<Object>& getObjects();
	std::vector<LightObject>& getLightObjects();

	void addObject(Object);
	void addLightObject(LightObject);

private:
	std::vector<Object> objects;
	std::vector<LightObject> lightObjects;
	camera camera;
};

