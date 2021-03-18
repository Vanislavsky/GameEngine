//В шейдерах e4.vs тоже нужно дописать код

#pragma once

#include <iostream>

//glew
#include <GL/glew.h>

//sfml
#include <SFML/Window.hpp>


#include "stb_image.h"
#include "shaderLoader.h"
#include"mat4.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Интерфейс можно менять как угодно
class Camera {
public:
	enum class ProjectionMode {
		ORTHOGRAPHIC,
		PERSPECTIVE
	};
	Camera() {

	}

	float GetFov() const;
	float GetRatio() const;
	float GetNear() const;
	float GetFar() const;
	void SetFov(float p_value);
	void SetRatio(float p_value);
	void SetNear(float p_value);
	void SetFar(float p_value);

	const mat4& GetProjectionMatrix() const {
		return m_projectionMatrix;
	}

	const mat4& GetViewMatrix() const {
		return m_viewMatrix;
	}

	const mat4& GetModelMatrix() const {
		return m_modelMatrix;
	}

	void set_view(mat4& _mat) {
		m_viewMatrix = _mat;
	}

	void set_projection(mat4& _mat) {
		m_projectionMatrix = _mat;
	}

	void set_model(mat4& _mat) {
		m_modelMatrix = _mat;
	}

private:
	mat4 m_viewMatrix;
	mat4 m_projectionMatrix;
	mat4 m_modelMatrix;
	ProjectionMode m_projectionMode;

	float m_fov;
	float m_ratio;
	float m_near;
	float m_far;
};


int main() {
	sf::ContextSettings settings;
	settings.depthBits = 24; // количество битов буффера глубины
	settings.stencilBits = 8; //количество битов буфера трафарета, используется с буфером глубины для ограничения области рендеринга
	settings.majorVersion = 4;
	settings.minorVersion = 3;
	settings.attributeFlags = sf::ContextSettings::Core;

	//sf::VideoMode(ширина, высота, кол-во бидля для цвета на 1 пиксель)
	sf::Window window(sf::VideoMode(800, 600, 32), "First Window",
		sf::Style::Titlebar | sf::Style::Close);

	glewExperimental = GL_TRUE; // включить все современные функции ogl

	if (GLEW_OK != glewInit()) { // включить glew
		std::cout << "Error:: glew not init =(" << std::endl;
		return -1;
	}

	auto shaderProgram = LoadShaders("C:/Users/79242/Desktop/res/shaders/e4.vs", "C:/Users/79242/Desktop/res/shaders/e4.fs");

	Camera* camera = new Camera();

	float vertices[] = {
		//x      y     z      u     v
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // левая нижняя
		-0.5f, 0.5f, 0.0f,   0.0f, 1.0f,// левая верхняя
		 0.5f, 0.5f, 0.0f,   1.0f, 1.0f,// правая верхняя
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f // правая нижняя
	};

	//EBO позволит использовать одни и те же вершины в разных треугольниках
	unsigned int indices[] = {
		0, 1, 3, // первый треугольник
		1, 2, 3  // второй треугольник
	};

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

	// цикл рендера
	bool isGo = true;
	while (isGo) {

		// обработка ивентов от SFML (тут и мышь и клавиши обрабатываются)
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent)) { // обработка ивентов

			//<YOUR CODE>

				//обработка клавиш и обновление позиции камеры
				//обработка мыши и обновления повотора камеры например с помошью углов эйлера
			switch (windowEvent.type) {
			case sf::Event::Closed:
				isGo = false;
				break;
			default:
				break;
			}
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //задали цвет отчистки
		glClear(GL_COLOR_BUFFER_BIT);                      //отчистка экрана

		glBindTexture(GL_TEXTURE_2D, texture); //связали текстуру

		glUseProgram(shaderProgram); // установили нужную шейдерную программу
		glBindVertexArray(VAO);      // установили нужный массив для рендеринга
		//glDrawArrays(GL_TRIANGLES, 0, 6); //отрисовали


		/*vec3 rotate_vec(1.0f, 0.0f, 0.0f);
		auto rotat = rotate(-55.0f, rotate_vec);

		vec3 trans_vec(0.0f, 0.0f, -3.0f);
		auto trans = translate(trans_vec);

		auto proj = perspective(45.0f, (GLfloat)300 / (GLfloat)200, 0.1f, 100.0f);


		camera->set_model(rotat);
		camera->set_projection(proj);
		camera->set_view(trans);

		auto model = camera->GetModelMatrix();
		auto view = camera->GetViewMatrix();
		auto prj = camera->GetProjectionMatrix();*/

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		model = glm::rotate(model, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);

		//для отрисовки с EBO ипользуется glDrawElements
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		window.display();
	}


	window.close();
	return 0;
}