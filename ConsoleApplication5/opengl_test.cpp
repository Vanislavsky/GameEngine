#include <iostream>

//glew
#include <GL/glew.h>

//sfml
#include <SFML/Window.hpp>

#include"mat4.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


static int test() {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	model = glm::rotate(model, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);

	mat4 model_2;
	vec3 a(1.0f, 0.0f, 0.0f);
	model_2 = rotate(-55.0f, a);

	std::cout << model_2(1, 2);
	std::cout << "TESTING";




	return 0;
}