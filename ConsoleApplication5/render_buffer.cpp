#include "render_buffer.h"

render_buffer::render_buffer() {
	glGenRenderbuffers(1, &ID);
	glBindRenderbuffer(GL_RENDERBUFFER, ID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1800, 1600);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, ID);
}

render_buffer::~render_buffer() {
	glDeleteRenderbuffers(1, &ID);
}