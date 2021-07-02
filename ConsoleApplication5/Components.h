
#pragma once
#include"shader_wrapper.h"
#include"texture.h"
#include"render_buffer.h"
#include"frame_buffer.h"
#include"camera.h"
#include"glm/glm.hpp"
#include"Model.h"
#include"vec3.h"
#include<map>

static class Components
{
public:
	static void init();
	static int verticesSize();
	static int quadVerticesSize();

	static void addModelComponent(unsigned int id);
	static void addColorComponent(unsigned int id);

	static shader_wrapper geometry_shader;
	static shader_wrapper lighting_shader;
	static shader_wrapper light_cube_shader;
	static frame_buffer gBuffer;
	static texture gPosition;
	static texture gNormal;
	static texture gAlbedoSpec;
	static render_buffer rboDepth;
	static float quadVertices[];
	static float vertices[];
	static camera cam;

	static std::map<unsigned int, Model> model_component;
	static std::map<unsigned int, vec3> light_component;
};

