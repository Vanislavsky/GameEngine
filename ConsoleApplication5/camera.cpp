#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

camera::camera() {

}

float camera::get_fov() const {
	return m_fov;
}
float camera::fetRatio() const {
	return m_ratio;
}
float camera::get_near() const {
	return m_near;
}
float camera::get_far() const {
	return m_far;
}
vec3 camera::get_position() {
	return position;
}

vec3 camera::get_front() {
	return front;
}

vec3 camera::get_up() {
	return up;
}

void camera::set_fov(float p_value) {
	m_fov = p_value;
}

void camera::set_ratio(float p_value) {
	m_ratio = p_value;
}

void camera::set_near(float p_value) {
	m_near = p_value;
}
void camera::set_far(float p_value) {

}
void camera::set_postion(vec3 p_pos) {
	position = p_pos;
}

void camera::set_front(vec3 p_front) {
	front = p_front;
}

void camera::set_up(vec3 p_up) {
	up = p_up;
}

mat4 camera::get_projection_matrix() const {
	return perspective(m_fov, m_ratio, m_near, m_far);
}
mat4 camera::get_view_matrix() {
	auto goal = position + front;
	return look_at(position, goal, up);
}

mat4 camera::get_view_mat3() {
	auto goal = position + front;
	mat4 res = look_at(position, goal, up);
	res.set_value(0, 0, 3);
	res.set_value(0, 1, 3);
	res.set_value(0, 2, 3);
	res.set_value(0, 3, 3);

	return res;
}

mat4 camera::get_model_matrix(float angle, const vec3& arbitrary_unit) const {
	return rotate(angle, arbitrary_unit);
}

mat4 camera::get_translate_matrix(vec3& translate_vec) const {
	return translate(translate_vec);
}

void camera::update_canera_vectors() {
	vec3 new_front;
	new_front.set_a1(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
	new_front.set_a2(sin(glm::radians(pitch)));
	new_front.set_a3(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));

	front = new_front.normal();
	right = front.vector_product(world_up).normal();
	up = right.vector_product(front).normal();
}