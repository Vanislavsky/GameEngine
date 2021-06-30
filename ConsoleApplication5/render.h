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

class Render
{
private:
	//camera* cam;
	//std::vector<Object*> objects;
	//std::vector<LightObject*> lightObjects;
public:
	Render();
	void rendering(camera* cam, std::vector<Object>& objects, std::vector<LightObject>& lightObjects, frame_buffer* gBuffer, texture* gPosition, texture* gNormal, texture* gAlbedoSpec, shader_wrapper* geometry_shader, shader_wrapper* lighting_shader, shader_wrapper* light_cube_shader);
	void renderQuad();
	void renderCube();

	void addObjects();
	void addLightObjects();

};

