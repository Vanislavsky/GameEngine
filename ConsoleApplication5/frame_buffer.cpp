#include "frame_buffer.h"


frame_buffer::frame_buffer() {
	glGenFramebuffers(1, &ID);
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

frame_buffer::~frame_buffer() {
	glDeleteFramebuffers(1, &ID);
}

void frame_buffer::bind(GLenum target) {
	glBindFramebuffer(target, ID);
}

void frame_buffer::bind(GLenum target, unsigned int buffer) {
	glBindFramebuffer(target, buffer);
}

void frame_buffer::blit(GLint srcX0,
    GLint srcY0,
    GLint srcX1,
    GLint srcY1,
    GLint dstX0,
    GLint dstY0,
    GLint dstX1,
    GLint dstY1,
    GLbitfield mask,
    GLenum filter) {
    glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}