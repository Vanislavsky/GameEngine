#include "Object.h"


Object::Object(unsigned int _id, vec3 _position) : id(_id), position(_position) {}

unsigned int Object::getId() {
	return id;
}

void Object::setPosition(vec3 _position) {
	position = _position;
}

vec3 Object::getPosition() {
	return position;
}


void Object::drawObject() {
	if (Components::model_component.find(id) != Components::model_component.end()) {
		vec3 scale_vec(0.2f, 0.2f, 0.2f);
		vec3 pos = position;
		auto model_tr = translate(pos);
		model_tr = model_tr * scale(scale_vec);
		Components::geometry_shader.set_mat4("model", model_tr, true);
		Components::model_component[id].Draw(Components::geometry_shader);
	}
}

void Object::lightingPassage() {
	if (Components::light_component.find(id) != Components::light_component.end()) {
		Components::lighting_shader.set_vec3("lights[" + std::to_string(id) + "].Position", position);
		Components::lighting_shader.set_vec3("lights[" + std::to_string(id) + "].Color", Components::light_component[id]);
		// update attenuation parameters and calculate radius
		const float constant = 1.0; // note that we don't send this to the shader, we assume it is always 1.0 (in our case)
		const float linear = 0.7;
		const float quadratic = 1.8;
		Components::lighting_shader.set_float("lights[" + std::to_string(id) + "].Linear", linear);
		Components::lighting_shader.set_float("lights[" + std::to_string(id) + "].Quadratic", quadratic);
		// then calculate radius of light volume/sphere
		const float maxBrightness = std::fmaxf(std::fmaxf(Components::light_component[id].get_a1(), Components::light_component[id].get_a2()), Components::light_component[id].get_a3());
		float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);
		Components::lighting_shader.set_float("lights[" + std::to_string(id) + "].Radius", radius);
	}
}

void Object::renderingLightingSources() {
	if (Components::light_component.find(id) != Components::light_component.end()) {
		vec3 scale_vec(0.2f, 0.2f, 0.2f);
		auto model_tr = translate(position);
		model_tr = model_tr * scale(scale_vec);
		Components::light_cube_shader.set_mat4("model", model_tr, true);
		Components::light_cube_shader.set_vec3("lightColor", Components::light_component[id]);

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
}