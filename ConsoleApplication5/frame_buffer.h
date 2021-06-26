#pragma once

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class frame_buffer
{
public:
    frame_buffer();

    ~frame_buffer();

    void bind(GLenum);
    void bind(GLenum, unsigned int);
    void unbind();

    void blit(GLint srcX0,
        GLint srcY0,
        GLint srcX1,
        GLint srcY1,
        GLint dstX0,
        GLint dstY0,
        GLint dstX1,
        GLint dstY1,
        GLbitfield mask,
        GLenum filter);


private:
    unsigned int ID;
};

