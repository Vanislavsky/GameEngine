
#pragma once
#include"shader_wrapper.h"
#include"texture.h"
#include"render_buffer.h"
#include"frame_buffer.h"
#include"camera.h"
#include"glm/glm.hpp"
#include"Model.h"
#include"vec3.h"

static class Components
{
public:
	static void init();
	static int verticesSize();
	static int quadVerticesSize();

	static shader_wrapper geometry_shader;
	static shader_wrapper lighting_shader;
	static shader_wrapper light_cube_shader;
	static frame_buffer gBuffer;
	static texture gPosition;
	static texture gNormal;
	static texture gAlbedoSpec;
	static render_buffer rboDepth;
	
	static Model model;
	static vec3 light;

	static float quadVertices[];
	static float vertices[];

	static camera cam;
};

