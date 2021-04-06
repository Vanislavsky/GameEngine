#pragma once

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class uniform_array
{
public:
	uniform_array();
	~uniform_array();

	void vertex_attrib_pointer(GLuint index,
		GLint size,
		GLenum type,
		GLboolean normalized,
		GLsizei stride,
		const GLvoid* pointer);

	void bind();

private:
	unsigned int ID;
};

