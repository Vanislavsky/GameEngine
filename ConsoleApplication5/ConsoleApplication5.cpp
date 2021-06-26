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
#include"render_buffer.h"
#include"frame_buffer.h"
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
void renderQuad();
void renderCube();

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

	shader_wrapper geometry_shader("g_buffer.vs", "g_buffer.fs");
	shader_wrapper lighting_shader("deferred_shading.vs", "deffered_shading.fs");
	shader_wrapper light_cube_shader("defered_light_box.vs", "deferred_light_box.fs");
	//shader_wrapper skyboxShader("skybox.vs", "skybox.fs");


	camera camera;
	//float fow, float ratio, float near, float far
	camera.set_fov(glm::radians(45.0f));
	camera.set_ratio((GLfloat)1800 / (GLfloat)1600);
	camera.set_near(0.1f);
	camera.set_far(100.0f);
	camera.set_postion({ 0.0f, 0.0f,  3.0f });
	camera.set_front({ 0.0f, 0.0f, -1.0f });
	camera.set_up({ 0.0f, 1.0f, 0.0f });



	frame_buffer gBuffer;


	texture gPosition(0);
	texture gNormal(1);
	texture gAlbedoSpec(2);
	

	// Сообщаем OpenGL, какой прикрепленный цветовой буфер (задействованного фреймбуфера) собираемся использовать для рендеринга
	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);

	// Создаем и прикрепляем буфер глубины (рендербуфер)
	render_buffer rboDepth;


	// Проверяем готовность фреймбуфера
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	std::cout << "Framebuffer not complete!" << std::endl;
	gBuffer.bind(GL_FRAMEBUFFER, 0);

	const unsigned int NR_LIGHTS = 32;
	std::vector<vec3> lightPositions;
	std::vector<vec3> lightColors;
	srand(13);
	for (unsigned int i = 0; i < NR_LIGHTS; i++)
	{
		// calculate slightly random offsets
		float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
		float yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
		float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
		lightPositions.push_back(vec3(xPos, yPos, zPos));
		// also calculate random color
		float rColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
		float gColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
		float bColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
		lightColors.push_back(vec3(rColor, gColor, bColor));
	}


	lighting_shader.use();
	lighting_shader.set_int("gPosition", 0);
	lighting_shader.set_int("gNormal", 1);
	lighting_shader.set_int("gAlbedoSpec", 2);
	

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
	objectPositions.push_back(vec3(4.7f, 0.0, 4.0f));
	objectPositions.push_back(vec3(3.7f, 0.0, 3.7f));
	objectPositions.push_back(vec3(-3.7f, 0.0, -3.7f));
	objectPositions.push_back(vec3(0.0f, 4.7f, 4.0f));

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

		// 1. Геометрический проход: выполняем рендеринг геометрических/цветовых данных сцены в g-буфер
		gBuffer.bind(GL_FRAMEBUFFER);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		

		mat4 proj = perspective(glm::radians(45.0f), (GLfloat)1800 / (GLfloat)1600, 0.1f, 100.0f);
		auto view = camera.get_view_matrix();
		geometry_shader.use();
		geometry_shader.set_mat4("projection", proj, true);
		geometry_shader.set_mat4("view", view, false);

		for (int i = 0; i < objectPositions.size(); i++) {
			vec3 scale_vec(0.2f, 0.2f, 0.2f);
			auto model_tr = translate(objectPositions[i]);
			model_tr = model_tr * scale(scale_vec);
			geometry_shader.set_mat4("model", model_tr, true);
			Model.Draw(geometry_shader);
		}
		gBuffer.bind(GL_FRAMEBUFFER, 0);


		
		// 2. Проход освещения
		gPosition.bind(0);
		gNormal.bind(1);
		gAlbedoSpec.bind(2);

		lighting_shader.use();

		for (unsigned int i = 0; i < lightPositions.size(); i++)
		{

			lighting_shader.set_vec3("lights[" + std::to_string(i) + "].Position", lightPositions[i]);
			lighting_shader.set_vec3("lights[" + std::to_string(i) + "].Color", lightColors[i]);
			// update attenuation parameters and calculate radius
			const float constant = 1.0; // note that we don't send this to the shader, we assume it is always 1.0 (in our case)
			const float linear = 0.7;
			const float quadratic = 1.8;
			lighting_shader.set_float("lights[" + std::to_string(i) + "].Linear", linear);
			lighting_shader.set_float("lights[" + std::to_string(i) + "].Quadratic", quadratic);
			// then calculate radius of light volume/sphere
			const float maxBrightness = std::fmaxf(std::fmaxf(lightColors[i].get_a1(), lightColors[i].get_a2()), lightColors[i].get_a3());
			float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);
			lighting_shader.set_float("lights[" + std::to_string(i) + "].Radius", radius);
		}
		lighting_shader.set_vec3("viewPos", camera.get_position());
		// finally render quad
		renderQuad();


		// 2.5. Копируем содержимое буфера глубины (геометрический проход) в буфер глубины заданного по умолчанию фреймбуфера
		gBuffer.bind(GL_READ_FRAMEBUFFER);
		gBuffer.bind(GL_DRAW_FRAMEBUFFER, 0); // write to default buffer
		// blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
		// the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
		// depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
		gBuffer.blit(0, 0, 1800, 1600, 0, 0, 1800, 1600, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
		gBuffer.bind(GL_DRAW_FRAMEBUFFER, 0);

		// 3. Рендерим источники освещения вверху сцены
		light_cube_shader.use();
		light_cube_shader.set_mat4("projection", proj, true);
		light_cube_shader.set_mat4("view", view, false);
		for (unsigned int i = 0; i < lightPositions.size(); i++)
		{

			vec3 scale_vec(0.2f, 0.2f, 0.2f);
			auto model_tr = translate(lightPositions[i]);
			model_tr = model_tr * scale(scale_vec);
			light_cube_shader.set_mat4("model", model_tr, true);
			light_cube_shader.set_vec3("lightColor", lightColors[i]);
			renderCube();
		}

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



void renderCube()
{

	float vertices[] = {
		// back face
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
		1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
		1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
			// front face
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
		1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
		1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
		1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
		-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			// left face
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			// right face
		1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
		1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
		1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
		1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
		1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
		1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
			// bottom face
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
		1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
		1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
		1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
		-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			// top face
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
		1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
		1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
		1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
		-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
	};

	uniform_array vertex_arrays_ob;
	uniform_buffer vertex_buffer_ob(vertices, sizeof(vertices) / sizeof(float));
	// link vertex attributes
	vertex_arrays_ob.bind();
	vertex_arrays_ob.vertex_attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	vertex_arrays_ob.vertex_attrib_pointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vertex_arrays_ob.vertex_attrib_pointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	vertex_buffer_ob.bind();

	// render Cube
	vertex_arrays_ob.bind();

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}


// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{

	float quadVertices[] = {
		// positions        // texture Coords
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};
	// setup plane VAO

	uniform_array vertex_arrays_ob;
	uniform_buffer vertex_buffer_ob(quadVertices, sizeof(quadVertices) / sizeof(float));
	vertex_arrays_ob.bind();
	vertex_buffer_ob.bind();
	vertex_arrays_ob.vertex_attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	vertex_arrays_ob.vertex_attrib_pointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	vertex_arrays_ob.bind();


	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}