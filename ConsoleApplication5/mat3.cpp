#include "mat3.h"
#include "mat2.h"
#include<cmath>

mat3::mat3() {
	data.resize(3);
	for (int i = 0; i < 3; i++)
		data[i].resize(3);
}

mat3::mat3(float el) {
	data.resize(3);
	for (int i = 0; i < 3; i++)
		data[i].resize(3);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			data[i][j] = el;
		}
	}
}

mat3::mat3(const std::vector<float>& _data) {
	data.resize(3);
	for (int i = 0; i < 3; i++)
		data[i].resize(3);

	int i = 0;
	int j = 0;
	for (auto it = _data.begin(); it != _data.end(); it++) {
		data[i][j] = *it;
		j++;
		if (j == 3) {
			i++;
			j = 0;
		}
	}
}

mat3::mat3(const mat3& _mat) {
	data.resize(3);
	for (int i = 0; i < 3; i++)
		data[i].resize(3);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			data[i][j] = _mat.data[i][j];
		}
	}
}

float mat3::get_value(int row, int col) {
	if (row > 3 || col > 3)
		return -1;
	else
		return data[row][col];
}

void mat3::set_value(float value, int row, int col) {
	if (row < 3 || col < 3)
		data[row][col] = value;
}

mat3 mat3::operator+(const mat3& _mat) {
	mat3 res_mat;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			res_mat.data[i][j] = data[i][j] + _mat.data[i][j];
		}
	}

	return res_mat;
}

mat3 mat3::operator-(const mat3& _mat) {
	mat3 res_mat;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			res_mat.data[i][j] = data[i][j] - _mat.data[i][j];
		}
	}

	return res_mat;
}

mat3 mat3::operator*(const mat3& _mat) {
	mat3 res_mat;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			res_mat.data[i][j] = 0;
			for (int k = 0; k < 3; k++) {
				res_mat.data[i][j] += data[i][k] * _mat.data[k][j];
			}
		}
	}

	return res_mat;
}

mat3 mat3::operator*(float value) {
	mat3 res_mat;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			res_mat.data[i][j] = data[i][j] * value;
		}
	}

	return res_mat;
}

vec3 mat3::operator*(vec3& _vec) {
	float temp_a1 = data[0][0] * _vec.get_a1() + data[0][1] * _vec.get_a2() + data[0][2] * _vec.get_a3();
	float temp_a2 = data[1][0] * _vec.get_a1() + data[1][1] * _vec.get_a2() + data[1][2] * _vec.get_a3();
	float temp_a3 = data[2][0] * _vec.get_a1() + data[2][1] * _vec.get_a2() + data[2][2] * _vec.get_a3();

	return { temp_a1, temp_a2, temp_a3 };
}

mat3 mat3::operator/(float value) {
	mat3 res_mat;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			res_mat.data[i][j] = data[i][j] / value;
		}
	}

	return res_mat;
}

float mat3::determinant() {
	auto det = data[0][0] * data[1][1] * data[2][2] + data[0][1] * data[1][2] * data[2][0] + data[0][2] * data[1][0] * data[2][1];
	auto rev_det = -data[0][2] * data[1][1] * data[2][0] - data[0][1] * data[1][0] * data[2][2] - data[0][0] * data[1][2] * data[2][1];
	return det + rev_det;
}

mat3 mat3::transposed_mat3() {
	mat3 res_mat = *this;

	float temp;
	for (int i = 0; i < 3; ++i) {
		for (int j = i; j < 3; ++j) {
			temp = res_mat.data[i][j];
			res_mat.data[i][j] = res_mat.data[j][i];
			res_mat.data[j][i] = temp;
		}
	}
	return res_mat;
}

float mat3::algebraic_addition(int row_index, int col_index) {
	mat2 minor_mat;
	int r = 0;
	int c = 0;
	for (int i = 0; i < 3; i++) {
		if (i == row_index)
			break;
		for (int j = 0; j < 3; j++) {
			if (j == col_index)
				break;
			minor_mat.set_value(data[i][j], r, c);
			c++;
			if (c == 3) {
				c = 0;
				r++;
			}
		}
	}

	return minor_mat.determinant() * pow(-1, row_index + col_index);
}

mat3 mat3::algebraic_additions_mat3() {
	std::vector<float> algebraic_additions_vector{ algebraic_addition(0, 0), algebraic_addition(0, 1), algebraic_addition(0, 2), algebraic_addition(1,0),
				algebraic_addition(1, 1), algebraic_addition(1, 2), algebraic_addition(2, 0), algebraic_addition(2, 1), algebraic_addition(2, 2) };
	return { algebraic_additions_vector };
}

mat3 mat3::reverse_mat3() {
	return  algebraic_additions_mat3().transposed_mat3() * (1 / determinant());
}

bool mat3::operator==(const mat3& _mat) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (data[i][j] != _mat.data[i][j]) {
				return false;
			}
		}
	}

	return true;
}
bool mat3::operator!=(const mat3& _mat) {
	return !(*this == _mat);
}

mat3 unit_mat3() {
	mat3 unit_mat3;
	unit_mat3.set_value(1, 0, 0);
	unit_mat3.set_value(1, 1, 1);
	unit_mat3.set_value(1, 2, 2);
	return unit_mat3;
}