
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

void shader_wrapper::set_int(const std::string& name, int value) {
	glUniform1i(glGetUniformLocation(shader_id, name.c_str()), value);
}

void shader_wrapper::set_vec3(const std::string& name, const vec3& value) {
	glUniform3fv(glGetUniformLocation(shader_id, name.c_str()), 1, value.transform_for_shader());
}

void shader_wrapper::set_float(const std::string& name, float value) {
	glUniform1f(glGetUniformLocation(shader_id, name.c_str()), value);
}

GLuint shader_wrapper::get_shader_id() {
	return shader_id;
}