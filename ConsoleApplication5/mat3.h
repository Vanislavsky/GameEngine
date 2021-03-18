#pragma once
#pragma once

#include<vector>
#include"vec3.h"

class mat3
{
public:
	mat3();
	mat3(float);
	mat3(const std::vector<float>&);
	mat3(const mat3&);

	float get_value(int, int);
	void set_value(float, int, int);

	mat3 operator+(const mat3&);
	mat3 operator-(const mat3&);
	mat3 operator*(const mat3&);
	mat3 operator*(float);
	vec3 operator*(vec3&);
	mat3 operator/(float);

	float determinant();
	mat3 transposed_mat3();
	float algebraic_addition(int, int);
	mat3 algebraic_additions_mat3();
	mat3 reverse_mat3();

	bool operator==(const mat3&);
	bool operator!=(const mat3&);

private:
	std::vector<std::vector<float>> data;
};


mat3 unit_mat3();