#pragma once
#include"Model.h"
#include"vec3.h"

#include"shader_wrapper.h"
#include"texture.h"
#include"render_buffer.h"
#include"frame_buffer.h"
#include"camera.h"

enum ObjectType{
	MODEL_OBJECT,
	LIGHT
};

class Object
{
public:
	Object(unsigned int _id, vec3);

	unsigned int getId();

	void setPosition(vec3);
	vec3 getPosition();

	void setTypeObject(ObjectType);
	ObjectType getType();

	Model* getModel();
	vec3* getColor();

	void addComponent(Model* _model);
	void addComponent(vec3* _colorLight);
private:
	vec3 position;
	unsigned int id;
	ObjectType objectType;

	Model* model = nullptr;
	vec3* colorLight = nullptr;
};

