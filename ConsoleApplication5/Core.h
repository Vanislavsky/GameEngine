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
#include"InputManager.h"
#include"render.h"
#include"Scene.h"

class Core
{
public:
	void init();
	void update();
	void postUpdate();

private:
	Window window;
	Render render;
	Scene scene;

};

