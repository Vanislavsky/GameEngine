#pragma once

#include"Object.h"
#include"LightObject.h"
#include<vector>
#include"camera.h"
#include"Components.h"

class Scene
{
public:
	std::vector<Object>& getObjects();
	std::vector<LightObject>& getLightObjects();

	void addObject(Object);
	void addLightObject(LightObject);

private:
	std::vector<Object> objects;
};

