#pragma once
#include"Model.h"
#include"vec3.h"

class Object
{
public:
	Object(string const&, vec3);

	unsigned int getId();

	void setPosition(vec3);
	vec3 getPosition();

	Model getModel();
private:
	Model model;
	vec3 position;
	unsigned int id;
};

