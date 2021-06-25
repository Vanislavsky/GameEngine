//В шейдерах e4.vs тоже нужно дописать код

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
#include"texture.h"

#include"math_test.h"

#include"camera.h"
#include"shader_wrapper.h"
#include"material.h"
#include"light_source.h"
#include"Model.h"


unsigned int loadTexture(const char* path);
void mouse_movement(camera& cam, float xpos, float ypos);
unsigned int loadCubemap(std::vector<std::string> faces);


GLfloat yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
GLfloat pitch = 0.0f;
GLfloat lastX = 1800 / 2.0;
GLfloat lastY = 1600 / 2.0;
bool firstMouse = true;
vec3 lightPos(1.2f, 1.0f, 2.0f);

int main() {

	sf::ContextSettings settings;
	settings.depthBits = 24; // количество битов буффера глубины
	settings.stencilBits = 8; //количество битов буфера трафарета, используется с буфером глубины для ограничения области рендеринга
	settings.majorVersion = 4;
	settings.minorVersion = 3;
	settings.attributeFlags = sf::ContextSettings::Core;

	//sf::VideoMode(ширина, высота, кол-во бидля для цвета на 1 пиксель)
	sf::Window window(sf::VideoMode(1800, 1600, 32), "First Window",
		sf::Style::Titlebar | sf::Style::Close, settings);

	glewExperimental = GL_TRUE; // включить все современные функции ogl

	glEnable(GL_DEPTH_TEST);

	if (GLEW_OK != glewInit()) { // включить glew
		std::cout << "Error:: glew not init =(" << std::endl;
		return -1;
	}

	shader_wrapper lightingShader("multieple_lights.vs", "multieple_lights.fs");
	shader_wrapper lightCubeShader("light_cube.vs", "light_cube.fs");
	shader_wrapper skyboxShader("skybox.vs", "skybox.fs");

	camera camera;
	//float fow, float ratio, float near, float far
	camera.set_fov(glm::radians(45.0f));
	camera.set_ratio((GLfloat)1800 / (GLfloat)1600);
	camera.set_near(0.1f);
	camera.set_far(100.0f);
	camera.set_postion({ 0.0f, 0.0f,  3.0f });
	camera.set_front({ 0.0f, 0.0f, -1.0f });
	camera.set_up({ 0.0f, 1.0f, 0.0f });

	material emerald(0, 1, 0.6f);

	float skyboxVertices[] = {
		// координаты         
	   -1.0f,  1.0f, -1.0f,
	   -1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
	   -1.0f,  1.0f, -1.0f,

	   -1.0f, -1.0f,  1.0f,
	   -1.0f, -1.0f, -1.0f,
	   -1.0f,  1.0f, -1.0f,
	   -1.0f,  1.0f, -1.0f,
	   -1.0f,  1.0f,  1.0f,
	   -1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

	   -1.0f, -1.0f,  1.0f,
	   -1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
	   -1.0f, -1.0f,  1.0f,

	   -1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
	   -1.0f,  1.0f,  1.0f,
	   -1.0f,  1.0f, -1.0f,

	   -1.0f, -1.0f, -1.0f,
	   -1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
	   -1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	//EBO позволит использовать одни и те же вершины в разных треугольниках
	unsigned int indices[] = {
		0, 1, 3, // первый треугольник
		1, 2, 3  // второй треугольник
	};

	vec3 cubePositions[] = {
		vec3(0.0f,  0.0f,  0.0f),
		vec3(2.0f,  5.0f, -15.0f),
		vec3(-1.5f, -2.2f, -2.5f),
		vec3(-3.8f, -2.0f, -12.3f),
		vec3(2.4f, -0.4f, -3.5f),
		vec3(-1.7f,  3.0f, -7.5f),
		vec3(1.3f, -2.0f, -2.5f),
		vec3(1.5f,  2.0f, -2.5f),
		vec3(1.5f,  0.2f, -1.5f),
		vec3(-1.3f,  1.0f, -1.5f)
	};

	light_source dir_light(light_source::DIRLIGHT);
	dir_light.set_direction({ -0.2f, -1.0f, -0.3f });
	dir_light.set_ambient({ 0.05f, 0.05f, 0.05f });
	dir_light.set_diffuse({ 0.4f, 0.4f, 0.4f });
	dir_light.set_specular({ 0.5f, 0.5f, 0.5f });

	std::vector<light_source> point_lights;
	point_lights.push_back({ light_source::POINTLIGHT, {0.7f,  0.2f,  2.0f}, { 0.05f, 0.05f, 0.05f },
		{ 0.8f, 0.8f, 0.8f }, { 1.0f, 1.0f, 1.0f }, 1.0f, 0.09,  0.032 });
	point_lights.push_back({ light_source::POINTLIGHT, {2.3f, -3.3f, -4.0f}, { 0.05f, 0.05f, 0.05f },
		{ 0.8f, 0.8f, 0.8f }, { 1.0f, 1.0f, 1.0f }, 1.0f, 0.09, 0.032 });
	point_lights.push_back({ light_source::POINTLIGHT, {-4.0f,  2.0f, -12.0f}, { 0.05f, 0.05f, 0.05f },
		 { 0.8f, 0.8f, 0.8f }, { 1.0f, 1.0f, 1.0f }, 1.0f,  0.09, 0.032 });
	point_lights.push_back({ light_source::POINTLIGHT, {0.0f,  0.0f, -3.0f}, { 0.05f, 0.05f, 0.05f },
		 { 0.8f, 0.8f, 0.8f }, { 1.0f, 1.0f, 1.0f }, 1.0f,  0.09, 0.032 });

	light_source spot(light_source::SPOTLIGHT, camera.get_position(), camera.get_front(), { 0.0f, 0.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, 1.0f, 0.09, 0.032, glm::cos(glm::radians(12.5f)),
		glm::cos(glm::radians(15.0f)));

	// 1. Настраиваем VAO (и VBO) 

	uniform_array skybox_arr;
	uniform_buffer skybox_buffer(skyboxVertices, sizeof(skyboxVertices) / sizeof(float));

	skybox_buffer.bind();

	skybox_arr.vertex_attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	uniform_array vertex_arrays_ob;
	uniform_buffer buffer_object(vertices, sizeof(vertices) / sizeof(float));

	vertex_arrays_ob.vertex_attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	vertex_arrays_ob.vertex_attrib_pointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vertex_arrays_ob.vertex_attrib_pointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));



	// 2. Настраиваем VAO света (VBO остается неизменным; вершины те же и для светового объекта, который также является 3D-кубом)
	uniform_array light_vertex_arrays_ob;

	buffer_object.bind();

	light_vertex_arrays_ob.vertex_attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	std::vector<std::string> faces
	{
		"../../../../Desktop/right.jpg",
		"../../../../Desktop/left.jpg",
		"../../../../Desktop/top.jpg",
		"../../../../Desktop/bottom.jpg",
		"../../../../Desktop/front.jpg",
		"../../../../Desktop/back.jpg"
	};
	unsigned int cubemapTexture = loadCubemap(faces);

	texture diffuse_map("../../../../Desktop/P163301-4-zoom-1.jpg");
	texture specular_map("../../../../Desktop/container_2_specular.png");

	lightingShader.use();
	lightingShader.set_int("material.diffuse", emerald.get_diffuse());
	lightingShader.set_int("material.specular", emerald.get_specular());

	skyboxShader.use();
	skyboxShader.set_int("skybox", 0);

	shader_wrapper load_shader("model_loading.vs", "model_loading.fs");
	stbi_set_flip_vertically_on_load(true);
	Model Model("C:/Users/79242/Desktop/backpack/backpack.obj");
	std::vector<vec3> objectPositions;
	objectPositions.push_back(vec3(-0.7f, 0.0f, 0.0f));
	objectPositions.push_back(vec3(0.0f, 0.0f, 0.0f));
	objectPositions.push_back(vec3(0.7f, 0.0, 0.0f));
	objectPositions.push_back(vec3(-0.7f, 0.0, 0.7f));
	objectPositions.push_back(vec3(0.0f, 0.0f, 0.7f));
	objectPositions.push_back(vec3(0.7f, 0.0, 0.7f));

	// цикл рендера
	bool isGo = true;
	while (isGo) {

		// обработка ивентов от SFML (тут и мышь и клавиши обрабатываются)
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent)) { // обработка ивентов

			//<YOUR CODE>

				//обработка клавиш и обновление позиции камеры
				//обработка мыши и обновления повотора камеры например с помошью углов эйлера
			GLfloat cameraSpeed = 0.05f;
			switch (windowEvent.type) {
			case sf::Event::Closed:
				isGo = false;
				break;
			case sf::Event::KeyPressed:
				if (windowEvent.key.code == sf::Keyboard::W) {
					auto pos_add = camera.get_front() * cameraSpeed;
					camera.set_postion(camera.get_position() - pos_add);
				}

				if (windowEvent.key.code == sf::Keyboard::S) {
					auto pos_min = camera.get_front() * cameraSpeed;
					camera.set_postion(camera.get_position() + pos_min);

				}

				if (windowEvent.key.code == sf::Keyboard::A) {
					auto pos_min = camera.get_front().vector_product(camera.get_up()).normal() * cameraSpeed;
					camera.set_postion(camera.get_position() - pos_min);
				}

				if (windowEvent.key.code == sf::Keyboard::D) {
					auto pos_add = camera.get_front().vector_product(camera.get_up()).normal() * cameraSpeed;
					camera.set_postion(camera.get_position() + pos_add);
				}
				break;

			case sf::Event::MouseMoved:
				mouse_movement(camera, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				break;
			default:
				break;
			}

		}

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //отчистка экрана

		load_shader.use();

		mat4 proj = perspective(glm::radians(45.0f), (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
		auto view = camera.get_view_matrix();
		load_shader.set_mat4("projection", proj, true);
		load_shader.set_mat4("view", view, false);

		/*for (int i = 0; i < objectPositions.size(); i++) {
			auto model_tr = translate(objectPositions[i]);
			model_tr = model_tr * scale(objectPositions[i]);
			load_shader.set_mat4("model", model_tr, true);

			Model.Draw(load_shader);
		}*/

		//auto model_tr = translate(objectPositions[0]);
		////model_tr = model_tr * scale(objectPositions[0]);
		//load_shader.set_mat4("model", model_tr, false);

		//Model.Draw(load_shader);
		/*vec3 model_vec(0.5f, -0.5f, 0.0f);
		auto model_tr = translate(model_vec);

		auto model = glm::mat4(1.0f);
		model = glm::translate(model, { 0.5f, -0.5f, 0.0f });

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << model[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << std::endl;


		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << model_tr.get_value(j, i) << " ";
			}
			std::cout << std::endl;
		}*/
		
		for (int i = 0; i < objectPositions.size(); i++) {
			vec3 scale_vec(0.2f, 0.2f, 0.2f);
			auto model_tr = translate(objectPositions[i]);
			model_tr = model_tr * scale(scale_vec);
			load_shader.set_mat4("model", model_tr, true);
			Model.Draw(load_shader);
		}

		/*vec3 model_vec(1.0f, 0.0f, 0.0f);
		vec3 scale_vec(0.2f, 0.2f, 0.2f);
		vec3 rotate_vec(1.0f, 0.0f, 0.0f);
		auto model_tr = translate(model_vec);
		model_tr = model_tr * scale(scale_vec);
		load_shader.set_mat4("model", model_tr, true);
		Model.Draw(load_shader);

		vec3 model_vec2(0.0f, 0.0f, 0.0f);
		vec3 scale_vec2(0.2f, 0.2f, 0.2f);
		vec3 rotate_vec2(1.0f, 0.0f, 0.0f);
		auto model_tr2 = translate(model_vec2);
		model_tr2 = model_tr2 * scale(scale_vec2);
		load_shader.set_mat4("model", model_tr2, true);
		Model.Draw(load_shader);*/

		lightingShader.use();
		lightingShader.set_vec3("viewPos", camera.get_position());
		lightingShader.set_float("material.shininess", emerald.get_shininess());


		// Направленный свет
		lightingShader.set_vec3("dirLight.direction", dir_light.get_direction());
		lightingShader.set_vec3("dirLight.ambient", dir_light.get_ambient());
		lightingShader.set_vec3("dirLight.diffuse", dir_light.get_diffuse());
		lightingShader.set_vec3("dirLight.specular", dir_light.get_specular());

		// Точечный источник света №1
		lightingShader.set_vec3("pointLights[0].position", point_lights[0].get_position());
		lightingShader.set_vec3("pointLights[0].ambient", point_lights[0].get_ambient());
		lightingShader.set_vec3("pointLights[0].diffuse", point_lights[0].get_diffuse());
		lightingShader.set_vec3("pointLights[0].specular", point_lights[0].get_specular());
		lightingShader.set_float("pointLights[0].constant", point_lights[0].get_constant());
		lightingShader.set_float("pointLights[0].linear", point_lights[0].get_linear());
		lightingShader.set_float("pointLights[0].quadratic", point_lights[0].get_quadratic());

		// Точечный источник света №2
		lightingShader.set_vec3("pointLights[1].position", point_lights[1].get_position());
		lightingShader.set_vec3("pointLights[1].ambient", point_lights[1].get_ambient());
		lightingShader.set_vec3("pointLights[1].diffuse", point_lights[1].get_diffuse());
		lightingShader.set_vec3("pointLights[1].specular", point_lights[1].get_specular());
		lightingShader.set_float("pointLights[1].constant", point_lights[1].get_constant());
		lightingShader.set_float("pointLights[1].linear", point_lights[1].get_linear());
		lightingShader.set_float("pointLights[1].quadratic", point_lights[1].get_quadratic());

		// Точечный источник света №3
		lightingShader.set_vec3("pointLights[2].position", point_lights[2].get_position());
		lightingShader.set_vec3("pointLights[2].ambient", point_lights[2].get_ambient());
		lightingShader.set_vec3("pointLights[2].diffuse", point_lights[2].get_diffuse());
		lightingShader.set_vec3("pointLights[2].specular", point_lights[2].get_specular());
		lightingShader.set_float("pointLights[2].constant", point_lights[2].get_constant());
		lightingShader.set_float("pointLights[2].linear", point_lights[2].get_linear());
		lightingShader.set_float("pointLights[2].quadratic", point_lights[2].get_quadratic());

		// Точечный источник света №4
		lightingShader.set_vec3("pointLights[3].position", point_lights[3].get_position());
		lightingShader.set_vec3("pointLights[3].ambient", point_lights[3].get_ambient());
		lightingShader.set_vec3("pointLights[3].diffuse", point_lights[3].get_diffuse());
		lightingShader.set_vec3("pointLights[3].specular", point_lights[3].get_specular());
		lightingShader.set_float("pointLights[3].constant", point_lights[3].get_constant());
		lightingShader.set_float("pointLights[3].linear", point_lights[3].get_linear());
		lightingShader.set_float("pointLights[3].quadratic", point_lights[3].get_quadratic());


		// Прожектор
		lightingShader.set_vec3("spotLight.position", spot.get_position());
		lightingShader.set_vec3("spotLight.direction", spot.get_direction());
		lightingShader.set_vec3("spotLight.ambient", spot.get_ambient());
		lightingShader.set_vec3("spotLight.diffuse", spot.get_diffuse());
		lightingShader.set_vec3("spotLight.specular", spot.get_specular());
		lightingShader.set_float("spotLight.constant", spot.get_constant());
		lightingShader.set_float("spotLight.linear", spot.get_linear());
		lightingShader.set_float("spotLight.quadratic", spot.get_quadratic());
		lightingShader.set_float("spotLight.cutOff", spot.get_cutOff());
		lightingShader.set_float("spotLight.outerCutOff", spot.get_outerCutOff());


		diffuse_map.bind(0);
		specular_map.bind(1);

		vertex_arrays_ob.bind();

		/*auto proj = perspective(glm::radians(45.0f), (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
		auto view = camera.get_view_matrix();
		lightingShader.set_mat4("view", view, false);
		auto prj = camera.get_projection_matrix();*/
		lightingShader.set_mat4("projection", proj, true);


		//for (int i = 0; i < 10; i++) {
		//	mat4 model_new = translate(cubePositions[i]);
		//	float angle = 20.0f * i;
		//	model_new = model_new * rotate(glm::radians(angle), vec3(1.0f, 0.3f, 0.5f));
		//	lightingShader.set_mat4("model", model_new, true);
		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}

		lightCubeShader.use();
		lightCubeShader.set_mat4("projection", proj, true);
		lightCubeShader.set_mat4("view", view, false);

		/*light_vertex_arrays_ob.bind();
		for (unsigned int i = 0; i < 4; i++)
		{
			auto t_mat = point_lights[i].get_position();
			mat4 light_model = translate(t_mat);
			vec3 scale_vec(0.4, 0.4, 0.4);
			light_model = light_model * scale(scale_vec);
			lightCubeShader.set_mat4("model", light_model, true);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}*/

		glm::vec3 vec1(camera.get_position().get_a1() , camera.get_position().get_a2(), camera.get_position().get_a3());
		glm::vec3 vec2((camera.get_position() + camera.get_front()).get_a1(), (camera.get_position() + camera.get_front()).get_a2(), (camera.get_position() + camera.get_front()).get_a3());
		glm::vec3 vec__3(camera.get_up().get_a1(), camera.get_up().get_a2(), camera.get_up().get_a3());
		mat4 sky_projection = perspective(glm::radians(45.0f), (float)1800 / (float)1600, 0.1f, 100.0f);
		glm::mat4 sky_view = glm::mat4(glm::mat3(glm::lookAt(vec1, vec2, vec__3)));


		//vec3 vec1_our(camera.get_position().get_a1(), camera.get_position().get_a2(), camera.get_position().get_a3());
		//vec3 vec2_our((camera.get_position() + camera.get_front()).get_a1(), (camera.get_position() + camera.get_front()).get_a2(), (camera.get_position() + camera.get_front()).get_a3());
		//vec3 vec__3_our(camera.get_up().get_a1(), camera.get_up().get_a2(), camera.get_up().get_a3());
		//mat4 our_sky_view = look_at(vec1_our, vec2_our, vec__3_our);

		//for (int i = 0; i < 4; i++) {
		//	for (int j = 0; j < 4; j++) {
		//		//std::cout << our_sky_view.get_value(i, j) << "  " << sky_view[i][j] << "    " << i << " " << j << std::endl;
		//		std::cout << our_sky_view.get_value(i, j) << " ";
		//	}
		//	std::cout << std::endl;
		//}


		glDepthFunc(GL_LEQUAL); // меняем функцию глубины, чтобы обеспечить прохождение теста глубины, когда значения равны содержимому буфера глубины
		skyboxShader.use();
		view = camera.get_view_mat3(); // убираем из матрицы вида секцию, отвечающую за операцию трансляции
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.get_shader_id(), "view"), 1, GL_FALSE, &sky_view[0][0]);
		//skyboxShader.set_mat4("view", our_sky_view, false);
		skyboxShader.set_mat4("projection", sky_projection, true);

		//// Куб скайбокса
		skybox_arr.bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // восстанавливаем стандартное значение функции теста глубины

		window.display();
	}


	window.close();
	return 0;
}


void mouse_movement(camera& cam, float xpos, float ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = lastX - xpos;
	GLfloat yoffset = ypos - lastY; // Reversed since y-coordinates go from bottom to left
	lastX = xpos;
	lastY = ypos;

	yaw += xoffset * 0.05;
	pitch += yoffset * 0.05;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	vec3 front;
	front.set_a1(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
	front.set_a2(sin(glm::radians(pitch)));
	front.set_a3(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));

	cam.set_front(front.normal());
}

unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

unsigned int loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
