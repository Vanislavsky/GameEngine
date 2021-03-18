#pragma once

#include<vector>
#include"vec2.h"

class mat2
{
public:
	mat2();
	mat2(float);
	mat2(const std::vector<float>&);
	mat2(const mat2&);

	float get_value(int, int);
	void set_value(float, int, int);

	mat2 operator+(const mat2&);
	mat2 operator-(const mat2&);
	mat2 operator*(const mat2&);
	mat2 operator*(float);
	vec2 operator*(vec2&);
	mat2 operator/(float);

	float determinant();
	mat2 transposed_mat2();
	mat2 algebraic_additions_mat2();
	mat2 reverse_mat2();

	bool operator==(mat2);
	bool operator!=(mat2);

private:
	std::vector<std::vector<float>> data;
};


mat2 unit_mat2();

