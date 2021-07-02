#pragma once
#include"Model.h"
#include"vec3.h"

#include"shader_wrapper.h"
#include"texture.h"
#include"render_buffer.h"
#include"frame_buffer.h"
#include"camera.h"
#include"Components.h"
#include"uniform_array.h"
#include"uniform_buffer.h"


class Object
{
public:
	Object(unsigned int _id, vec3);

	unsigned int getId();

	void setPosition(vec3);
	vec3 getPosition();

	void addComponent(Model* _model);
	void addComponent(vec3* _colorLight);

	void drawObject();
	void lightingPassage();
	void renderingLightingSources();
private:
	vec3 position;
	unsigned int id;
};

