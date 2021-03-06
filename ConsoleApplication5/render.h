#pragma once

#include <GL/glew.h>
#include <iostream>
#include"frame_buffer.h"
#include"render_buffer.h"
#include"texture.h"
#include"camera.h"
#include"Object.h"
#include"shader_wrapper.h"
#include <glm/glm.hpp>
#include"mat4.h"
#include"vec3.h"
#include"LightObject.h"
#include"uniform_array.h"
#include"uniform_buffer.h"
#include"Components.h"

class Render
{
private:
	//camera* cam;
	//std::vector<Object*> objects;
	//std::vector<LightObject*> lightObjects;
public:
	Render();
	void rendering(std::vector<Object>& objects);
	void renderQuad();
	void renderCube();

	void addObjects();
	void addLightObjects();

};

