
#include "shader_wrapper.h"
#include "shaderLoader.h"

shader_wrapper::shader_wrapper(const std::string& vertex_shader_path, const std::string& fragment_shader_path) {
	shader_id = LoadShaders(vertex_shader_path, fragment_shader_path);
}

void shader_wrapper::use() {
	glUseProgram(shader_id);
}
void shader_wrapper::set_mat4(const GLchar* name, mat4& mat, bool is_transpore) {
	if(is_transpore)
		glUniformMatrix4fv(glGetUniformLocation(shader_id, name), 1, GL_TRUE, mat.transform_for_shader());
	else
		glUniformMatrix4fv(glGetUniformLocation(shader_id, name), 1, GL_FALSE, mat.transform_for_shader());
}