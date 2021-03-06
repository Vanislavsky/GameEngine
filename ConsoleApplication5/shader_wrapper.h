#ifndef GAME_ENGINE_SHADER_WRAPPER
#define GAME_ENGINE_SHADER_WRAPPER



#include <GL/glew.h>
#include <string>
#include"mat4.h"

class shader_wrapper {
public:
	explicit shader_wrapper(const std::string&, const std::string&);

	GLuint get_shader_id();
	void use();
	void set_mat4(const GLchar*, mat4&, bool);
	void set_int(const std::string& name, int value);
	void set_vec3(const std::string& name, const vec3& value);
	void set_float(const std::string& name, float value);

private:
	GLuint shader_id;
};

#endif // !GAME_ENGINE_SHADER_WRAPPER
