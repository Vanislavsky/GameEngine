#pragma once
#pragma once

#include<vector>
#include"vec2.h"
#include"vec3.h"
#include"vec4.h"

class mat4
{
public:
	mat4();
	mat4(float);
	mat4(const std::vector<float>&);
	mat4(const mat4&);

	float get_value(int, int);
	const void set_value(const float, int, int);
	float& operator()(size_t, size_t);
	float* transform_for_shader();

	mat4 operator+(const mat4&);
	mat4 operator-(const mat4&);
	mat4 operator*(const mat4&);
	mat4 operator*(float);
	vec4 operator*(vec4&);
	mat4 operator/(float);

	float determinant();
	mat4 transposed_mat4();
	float algebraic_addition(int, int);
	mat4 algebraic_additions_mat4();
	mat4 reverse_mat4();

	bool operator==(mat4);
	bool operator!=(mat4);

private:
	std::vector<std::vector<float>> data;
};


mat4 unit_mat4();
mat4 translate(const vec3&);
mat4 scale(vec3&);
mat4 rotate(float, const vec3&);
mat4 r(vec4& _vec, float angle, vec3& arbitrary_axis);

mat4 look_at(vec3&, vec3&, vec3&);
mat4 perspective(float, float, float, float);
mat4 ortho(float left, float right, float bottom, float top, float near, float far);


