#pragma once

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class render_buffer
{
public:
    render_buffer();

    ~render_buffer();

private:
    unsigned int ID;
};

