//В шейдерах e4.vs тоже нужно дописать код

#pragma once

#include <iostream>
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

#include"math_test.h"

#include"camera.h"
#include"shader_wrapper.h"
#include"material.h"

unsigned int loadTexture(const char* path);
void mouse_movement(camera& cam, float xpos, float ypos);


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

	vec3 pointLightPositions[] = {
	   vec3(0.7f,  0.2f,  2.0f),
	   vec3(2.3f, -3.3f, -4.0f),
	   vec3(-4.0f,  2.0f, -12.0f),
	   vec3(0.0f,  0.0f, -3.0f)
	};

	// 1. Настраиваем VAO (и VBO) куба
	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// 2. Настраиваем VAO света (VBO остается неизменным; вершины те же и для светового объекта, который также является 3D-кубом)
	unsigned int lightCubeVAO;;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int diffuseMap = loadTexture("../../../../Desktop/P163301-4-zoom-1.jpg");
	unsigned int specularMap = loadTexture("../../../../Desktop/container_2_specular.png");

	lightingShader.use();
	lightingShader.set_int("material.diffuse", emerald.get_diffuse());
	lightingShader.set_int("material.specular", emerald.get_specular());
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
					camera.set_postion(camera.get_position() + pos_add);
				}

				if (windowEvent.key.code == sf::Keyboard::S) {
					auto pos_min = camera.get_front() * cameraSpeed;
					camera.set_postion(camera.get_position() - pos_min);
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

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //задали цвет отчистки
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //отчистка экрана
		lightingShader.use();
		lightingShader.set_vec3("viewPos", camera.get_position());
		lightingShader.set_float("material.shininess", emerald.get_shininess());


		// Направленный свет
		lightingShader.set_vec3("dirLight.direction", { -0.2f, -1.0f, -0.3f });
		lightingShader.set_vec3("dirLight.ambient", { 0.05f, 0.05f, 0.05f });
		lightingShader.set_vec3("dirLight.diffuse", { 0.4f, 0.4f, 0.4f });
		lightingShader.set_vec3("dirLight.specular", { 0.5f, 0.5f, 0.5f });

		// Точечный источник света №1
		lightingShader.set_vec3("pointLights[0].position", pointLightPositions[0]);
		lightingShader.set_vec3("pointLights[0].ambient", { 0.05f, 0.05f, 0.05f });
		lightingShader.set_vec3("pointLights[0].diffuse", { 0.8f, 0.8f, 0.8f });
		lightingShader.set_vec3("pointLights[0].specular", { 1.0f, 1.0f, 1.0f });
		lightingShader.set_float("pointLights[0].constant", 1.0f);
		lightingShader.set_float("pointLights[0].linear", 0.09);
		lightingShader.set_float("pointLights[0].quadratic", 0.032);

		// Точечный источник света №2
		lightingShader.set_vec3("pointLights[1].position", pointLightPositions[1]);
		lightingShader.set_vec3("pointLights[1].ambient", { 0.05f, 0.05f, 0.05f });
		lightingShader.set_vec3("pointLights[1].diffuse", { 0.8f, 0.8f, 0.8f });
		lightingShader.set_vec3("pointLights[1].specular", { 1.0f, 1.0f, 1.0f });
		lightingShader.set_float("pointLights[1].constant", 1.0f);
		lightingShader.set_float("pointLights[1].linear", 0.09);
		lightingShader.set_float("pointLights[1].quadratic", 0.032);

		// Точечный источник света №3
		lightingShader.set_vec3("pointLights[2].position", pointLightPositions[2]);
		lightingShader.set_vec3("pointLights[2].ambient", { 0.05f, 0.05f, 0.05f });
		lightingShader.set_vec3("pointLights[2].diffuse", { 0.8f, 0.8f, 0.8f });
		lightingShader.set_vec3("pointLights[2].specular", { 1.0f, 1.0f, 1.0f });
		lightingShader.set_float("pointLights[2].constant", 1.0f);
		lightingShader.set_float("pointLights[2].linear", 0.09);
		lightingShader.set_float("pointLights[2].quadratic", 0.032);

		// Точечный источник света №4
		lightingShader.set_vec3("pointLights[3].position", pointLightPositions[3]);
		lightingShader.set_vec3("pointLights[3].ambient", { 0.05f, 0.05f, 0.05f });
		lightingShader.set_vec3("pointLights[3].diffuse", { 0.8f, 0.8f, 0.8f });
		lightingShader.set_vec3("pointLights[3].specular", { 1.0f, 1.0f, 1.0f });
		lightingShader.set_float("pointLights[3].constant", 1.0f);
		lightingShader.set_float("pointLights[3].linear", 0.09);
		lightingShader.set_float("pointLights[3].quadratic", 0.032);

		// Прожектор
		lightingShader.set_vec3("spotLight.position", camera.get_position());
		lightingShader.set_vec3("spotLight.direction", camera.get_front());
		lightingShader.set_vec3("spotLight.ambient", { 0.0f, 0.0f, 0.0f });
		lightingShader.set_vec3("spotLight.diffuse", { 1.0f, 1.0f, 1.0f });
		lightingShader.set_vec3("spotLight.specular", { 1.0f, 1.0f, 1.0f });
		lightingShader.set_float("spotLight.constant", 1.0f);
		lightingShader.set_float("spotLight.linear", 0.09);
		lightingShader.set_float("spotLight.quadratic", 0.032);
		lightingShader.set_float("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		lightingShader.set_float("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);

		// Связывание карты отраженного цвета
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);


		//shader_program.use();
		glBindVertexArray(cubeVAO);      // установили нужный массив для рендеринга


		auto proj = perspective(glm::radians(45.0f), (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);


		//auto model = camera.get_model_matrix(glm::radians(-55.0f), { 1.0f, 0.0f, 0.0f });
		//auto view = camera.get_translate_matrix(trans_vec);


		auto view = camera.get_view_matrix();
		lightingShader.set_mat4("view", view, false);
		auto prj = camera.get_projection_matrix();
		lightingShader.set_mat4("projection", prj, true);


		for (int i = 0; i < 10; i++) {
			mat4 model_new = translate(cubePositions[i]);
			float angle = 20.0f * i;
			model_new = model_new * rotate(glm::radians(angle), vec3(1.0f, 0.3f, 0.5f));
			lightingShader.set_mat4("model", model_new, true);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		lightCubeShader.use();
		lightCubeShader.set_mat4("projection", prj, true);
		lightCubeShader.set_mat4("view", view, false);

		glBindVertexArray(lightCubeVAO);
		for (unsigned int i = 0; i < 4; i++)
		{
			mat4 light_model = translate(pointLightPositions[i]);
			vec3 scale_vec(0.4, 0.4, 0.4);
			light_model = light_model * scale(scale_vec);
			lightCubeShader.set_mat4("model", light_model, true);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glDrawArrays(GL_TRIANGLES, 0, 36);
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

	//GLfloat xoffset = xpos - lastX;
	//GLfloat yoffset = lastY - ypos;
	GLfloat xoffset = lastX - xpos;
	GLfloat yoffset = ypos - lastY; // Reversed since y-coordinates go from bottom to left
	lastX = xpos;
	lastY = ypos;

	//GLfloat sensitivity = 0.1;	// Change this value to your liking
	//xoffset *= sensitivity;
	//yoffset *= sensitivity;

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