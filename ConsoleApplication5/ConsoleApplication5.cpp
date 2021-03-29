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


void mouse_movement(camera& cam, float xpos, float ypos);


GLfloat yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
GLfloat pitch = 0.0f;
GLfloat lastX = 1800 / 2.0;
GLfloat lastY = 1600 / 2.0;
bool firstMouse = true;


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

	/*std::string vertex_shader_path("C:/Users/79242/Desktop/res/shaders/e4.vs");
	std::string fragment_shader_path("C:/Users/79242/Desktop/res/shaders/e4.fs");
	shader_wrapper shader_program(vertex_shader_path, fragment_shader_path);*/

	shader_wrapper lightingShader("light_casters.vs", "light_casters.fs");
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

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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

	vec3 CubePosition(1.5f, 0.2f, -1.5f);

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO); // сгенерили id для массивов вершин (у нас это один id)
	glBindVertexArray(VAO); // и связали массив с opengl

	glGenBuffers(1, &VBO); // сгенерили буфер данных размером 1
	glBindBuffer(GL_ARRAY_BUFFER, VBO);// и связали буфер с opengl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // прокинули наш масив вершин в opengl

	//Создали и связали EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // прописали параметры для объекта
	glEnableVertexAttribArray(0); //тк layout у позиции 0

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 2. Настраиваем VAO света (VBO остается неизменным; вершины те же и для светового объекта, который также является 3D-кубом)
	unsigned int lightCubeVAO;;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	// Загрузка и создание текстуры
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // все последующие GL_TEXTURE_2D-операции теперь будут влиять на данный текстурный объект

	// Установка параметров наложения текстуры
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // установка метода наложения текстуры GL_REPEAT (стандартный метод наложения)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Установка параметров фильтрации текстуры
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Загрузка изображения, создание текстуры и генерирование мипмап-уровней
	int width, height, nrChannels;
	/*
	 * По дефолту текстура перевернута вверх ногами.
	 * Это происходит потому, что OpenGL ожидает, что координата 0.0 на оси Y будет
	 * находиться в нижней части изображения, но изображения обычно имеют 0.0 в верхней
	 * части оси Y. stbi_set_flip_vertically_on_load исправит это!
	 */
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load("C:/Users/79242/Desktop/res/imgs/1.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	lightingShader.use();
	lightingShader.set_int("material.diffuse", 0);
	lightingShader.set_int("material.specular", 1);
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

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //задали цвет отчистки
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                      //отчистка экрана
		lightingShader.use();
		lightingShader.set_vec3("light.direction", { -0.2f, -1.0f, -0.3f });
		lightingShader.set_vec3("viewPos", camera.get_position());

		lightingShader.set_vec3("light.ambient", { 0.2f, 0.2f, 0.2f });
		lightingShader.set_vec3("light.diffuse", {0.5f, 0.5f, 0.5f});
		lightingShader.set_vec3("light.specular", { 1.0f, 1.0f, 1.0f });

		lightingShader.set_float("material.shininess", 32.0f);

		glBindTexture(GL_TEXTURE_2D, texture); //связали текстуру

		//shader_program.use();
		glBindVertexArray(VAO);      // установили нужный массив для рендеринга


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

		//shader_program.set_mat4("model", model, true);
		//shader_program.set_mat4("view", view, false);
		//shader_program.set_mat4("projection", prj, true);

		//glDrawArrays(GL_TRIANGLES, 0, 36);


		//для отрисовки с EBO ипользуется glDrawElements
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		window.display();
	}


	window.close();
	return 0;
}


void mouse_movement(camera& cam,float xpos, float ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;
	//GLfloat xoffset = lastX - xpos;
	//GLfloat yoffset = ypos - lastY; // Reversed since y-coordinates go from bottom to left
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



