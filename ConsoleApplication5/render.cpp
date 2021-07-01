#include "render.h"
#include"Components.h"

Render::Render() {
	glewExperimental = GL_TRUE; // включить все современные функции ogl

	glEnable(GL_DEPTH_TEST);

	if (GLEW_OK != glewInit()) { // включить glew
		std::cout << "Error:: glew not init =(" << std::endl;
	}

}

void Render::rendering(std::vector<Object>& objects) {
	Components::gBuffer.bind(GL_FRAMEBUFFER);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	mat4 proj = perspective(glm::radians(45.0f), (GLfloat)1800 / (GLfloat)1600, 0.1f, 100.0f);
	auto view = Components::cam.get_view_matrix();
	Components::geometry_shader.use();
	Components::geometry_shader.set_mat4("projection", proj, true);
	Components::geometry_shader.set_mat4("view", view, false);

	for (int i = 0; i < objects.size(); i++) {
		if (objects[i].getType() == ObjectType::MODEL_OBJECT) {
			vec3 scale_vec(0.2f, 0.2f, 0.2f);
			vec3 pos = objects[i].getPosition();
			auto model_tr = translate(pos);
			model_tr = model_tr * scale(scale_vec);
			Components::geometry_shader.set_mat4("model", model_tr, true);
			(*objects[i].getModel()).Draw(Components::geometry_shader);
		}
	}
	Components::gBuffer.bind(GL_FRAMEBUFFER, 0);

	// 2. Проход освещения
	Components::gPosition.bind(0);
	Components::gNormal.bind(1);
	Components::gAlbedoSpec.bind(2);

	Components::lighting_shader.use();

	for (unsigned int i = 0; i < objects.size(); i++)
	{
		if (objects[i].getType() == ObjectType::LIGHT) {
			Components::lighting_shader.set_vec3("lights[" + std::to_string(i) + "].Position", objects[i].getPosition());
			Components::lighting_shader.set_vec3("lights[" + std::to_string(i) + "].Color", *objects[i].getColor());
			// update attenuation parameters and calculate radius
			const float constant = 1.0; // note that we don't send this to the shader, we assume it is always 1.0 (in our case)
			const float linear = 0.7;
			const float quadratic = 1.8;
			Components::lighting_shader.set_float("lights[" + std::to_string(i) + "].Linear", linear);
			Components::lighting_shader.set_float("lights[" + std::to_string(i) + "].Quadratic", quadratic);
			// then calculate radius of light volume/sphere
			const float maxBrightness = std::fmaxf(std::fmaxf((*objects[i].getColor()).get_a1(), (*objects[i].getColor()).get_a2()), (*objects[i].getColor()).get_a3());
			float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);
			Components::lighting_shader.set_float("lights[" + std::to_string(i) + "].Radius", radius);
		}
	}

	Components::lighting_shader.set_vec3("viewPos", Components::cam.get_position());
	// finally render quad
	renderQuad();


	// 2.5. Копируем содержимое буфера глубины (геометрический проход) в буфер глубины заданного по умолчанию фреймбуфера
	Components::gBuffer.bind(GL_READ_FRAMEBUFFER);
	Components::gBuffer.bind(GL_DRAW_FRAMEBUFFER, 0); // write to default buffer
	// blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
	// the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
	// depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
	Components::gBuffer.blit(0, 0, 1800, 1600, 0, 0, 1800, 1600, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	Components::gBuffer.bind(GL_DRAW_FRAMEBUFFER, 0);

	// 3. Рендерим источники освещения вверху сцены
	Components::light_cube_shader.use();
	Components::light_cube_shader.set_mat4("projection", proj, true);
	Components::light_cube_shader.set_mat4("view", view, false);
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		if (objects[i].getType() == ObjectType::LIGHT) {
			vec3 scale_vec(0.2f, 0.2f, 0.2f);
			auto model_tr = translate(objects[i].getPosition());
			model_tr = model_tr * scale(scale_vec);
			Components::light_cube_shader.set_mat4("model", model_tr, true);
			Components::light_cube_shader.set_vec3("lightColor", *objects[i].getColor());
			renderCube();
		}
	}
}

void Render::renderQuad() {
	
	// setup plane VAO

	uniform_array vertex_arrays_ob;
	uniform_buffer vertex_buffer_ob(Components::quadVertices, Components::quadVerticesSize() / sizeof(float));
	vertex_arrays_ob.bind();
	vertex_buffer_ob.bind();
	vertex_arrays_ob.vertex_attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	vertex_arrays_ob.vertex_attrib_pointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	vertex_arrays_ob.bind();


	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}


void Render::renderCube() {
	

	uniform_array vertex_arrays_ob;
	uniform_buffer vertex_buffer_ob(Components::vertices, Components::verticesSize() / sizeof(float));
	// link vertex attributes
	vertex_arrays_ob.bind();
	vertex_arrays_ob.vertex_attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	vertex_arrays_ob.vertex_attrib_pointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vertex_arrays_ob.vertex_attrib_pointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	vertex_buffer_ob.bind();

	// render Cube
	vertex_arrays_ob.bind();

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}