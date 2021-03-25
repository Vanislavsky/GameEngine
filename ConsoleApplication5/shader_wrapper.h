#ifndef GAME_ENGINE_SHADER_WRAPPER
#define GAME_ENGINE_SHADER_WRAPPER



#include <GL/glew.h>
#include <string>
#include"mat4.h"

class shader_wrapper {
public:
	explicit shader_wrapper(const std::string&, const std::string&);

	void use();
	void set_mat4(const GLchar*, mat4&, bool);

private:
	GLuint shader_id;
};

#endif // !GAME_ENGINE_SHADER_WRAPPER
