#pragma once

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class uniform_buffer {
public:
    uniform_buffer(float vertices[]);

    ~uniform_buffer();

    void bind();
    void unbind();
private:
    unsigned int ID;
};

