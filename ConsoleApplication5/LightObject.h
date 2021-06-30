#pragma once

#include"vec3.h"

class LightObject
{
public:
	LightObject(vec3 _color, vec3 _position);

	void setPosition(vec3 _position);
	void setColor(vec3);

	vec3 getPosition();
	vec3 getColor();
	unsigned int getId();
private:
	vec3 position;
	vec3 color;
	unsigned int id;

};

