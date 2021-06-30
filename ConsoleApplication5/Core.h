#pragma once

#include <iostream>
#include<vector>
#include<string>

//glew
#include <GL/glew.h>

//sfml
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


#include "stb_image.h"
#include "shaderLoader.h"
#include"mat4.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"uniform_buffer.h"
#include"uniform_array.h"
#include"render_buffer.h"
#include"frame_buffer.h"
#include"texture.h"

#include"math_test.h"

#include"camera.h"
#include"shader_wrapper.h"
#include"material.h"
#include"light_source.h"
#include"Model.h"

#include "Window.h"

#include"render.h"
#include"Scene.h"

class Core
{
public:
	Core();
	void preUpdate();
	void upadte();
	void postUpdate();

private:
	Window window;
	//InputManager inputManager;
	Render render;
	shader_wrapper geometry_shader;
	shader_wrapper lighting_shader;
	shader_wrapper light_cube_shader;
	frame_buffer gBuffer;
	texture gPosition;
	texture gNormal;
	texture gAlbedoSpec;
	render_buffer rboDepth;
	Scene scene;

};

