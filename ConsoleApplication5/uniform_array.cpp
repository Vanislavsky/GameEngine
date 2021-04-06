#include "uniform_array.h"

uniform_array::uniform_array() {
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}
uniform_array::~uniform_array() {

}

void uniform_array::vertex_attrib_pointer(GLuint index,
	GLint size,
	GLenum type,
	GLboolean normalized,
	GLsizei stride,
	const GLvoid* pointer) {
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
}

void uniform_array::bind() {
	glBindVertexArray(ID);
}