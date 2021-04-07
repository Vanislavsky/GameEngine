#include "uniform_buffer.h"

uniform_buffer::uniform_buffer(float vertices[], int size) {
    auto a =sizeof(vertices);
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size*sizeof(vertices), vertices, GL_STATIC_DRAW);
}

uniform_buffer::~uniform_buffer() {
    glDeleteBuffers(1, &ID);
}

void uniform_buffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void uniform_buffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}