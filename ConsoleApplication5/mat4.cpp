#include "mat4.h"
#include "mat3.h"
#include<cmath>
#include<vector>

#define PI 3.14159265 

mat4::mat4() {
	data.resize(4);
	for (int i = 0; i < 4; i++)
		data[i].resize(4);
}

mat4::mat4(float el) {
	data.resize(4);
	for (int i = 0; i < 4; i++)
		data[i].resize(4);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			data[i][j] = el;
		}
	}
}

mat4::mat4(const std::vector<float>& _data) {
	data.resize(4);
	for (int i = 0; i < 4; i++)
		data[i].resize(4);

	int i = 0;
	int j = 0;
	for (auto it = _data.begin(); it != _data.end(); it++) {
		data[i][j] = *it;
		j++;
		if (j == 4) {
			i++;
			j = 0;
		}
	}
}

mat4::mat4(const mat4& _mat) {
	data.resize(4);
	for (int i = 0; i < 4; i++)
		data[i].resize(4);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			data[i][j] = _mat.data[i][j];
		}
	}
}

float mat4::get_value(int row, int col) {
	if (row > 4 || col > 4)
		return -1;
	else
		return data[row][col];
}



const void mat4::set_value(const float value, int row, int col) {
	if (row < 4 || col < 4)
		data[row][col] = value;
}

float& mat4::operator()(size_t i, size_t j) {
	return data[i][j];
}

float* mat4::transform_for_shader() {
	//std::vector<float> res();
	int z = 0;
	auto res = new float[16];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res[z] = data[i][j];
			z++;
			//res.push_back(data[i][j]);
		}
	}
	return res;
	//return &data[0][0];
}

mat4 mat4::operator+(const mat4& _mat) {
	mat4 res_mat;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res_mat.data[i][j] = data[i][j] + _mat.data[i][j];
		}
	}

	return res_mat;
}

mat4 mat4::operator-(const mat4& _mat) {
	mat4 res_mat;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res_mat.data[i][j] = data[i][j] - _mat.data[i][j];
		}
	}

	return res_mat;
}

mat4 mat4::operator*(const mat4& _mat) {
	mat4 res_mat;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res_mat.data[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				res_mat.data[i][j] += data[i][k] * _mat.data[k][j];
			}
		}
	}

	return res_mat;
}

mat4 mat4::operator*(float value) {
	mat4 res_mat;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res_mat.data[i][j] = data[i][j] * value;
		}
	}

	return res_mat;
}

vec4 mat4::operator*(vec4& _vec) {
	float temp_a1 = data[0][0] * _vec.get_a1() + data[0][1] * _vec.get_a2() + data[0][2] * _vec.get_a3() + data[0][3] * _vec.get_a4();
	float temp_a2 = data[1][0] * _vec.get_a1() + data[1][1] * _vec.get_a2() + data[1][2] * _vec.get_a3() + data[1][3] * _vec.get_a4();
	float temp_a3 = data[2][0] * _vec.get_a1() + data[2][1] * _vec.get_a2() + data[2][2] * _vec.get_a3() + data[2][3] * _vec.get_a4();
	float temp_a4 = data[3][0] * _vec.get_a1() + data[3][1] * _vec.get_a2() + data[3][2] * _vec.get_a3() + data[3][3] * _vec.get_a4();

	return { temp_a1, temp_a2, temp_a3, temp_a4 };
}

mat4 mat4::operator/(float value) {
	mat4 res_mat;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res_mat.data[i][j] = data[i][j] / value;
		}
	}

	return res_mat;
}

float mat4::determinant() {
	auto det = data[0][0] * data[1][1] * data[2][2] + data[0][1] * data[1][2] * data[2][0] + data[0][2] * data[1][0] * data[2][1];
	auto rev_det = -data[0][2] * data[1][1] * data[2][0] - data[0][1] * data[1][0] * data[2][2] - data[0][0] * data[1][2] * data[2][1];
	return det + rev_det;
}

mat4 mat4::transposed_mat4() {
	mat4 res_mat = *this;

	float temp;
	for (int i = 0; i < 4; ++i) {
		for (int j = i; j < 4; ++j) {
			temp = res_mat.data[i][j];
			res_mat.data[i][j] = res_mat.data[j][i];
			res_mat.data[j][i] = temp;
		}
	}
	return res_mat;
}

float mat4::algebraic_addition(int row_index, int col_index) {
	mat3 minor_mat;
	int r = 0;
	int c = 0;
	for (int i = 0; i < 4; i++) {
		if (i == row_index)
			break;
		for (int j = 0; j < 4; j++) {
			if (j == col_index)
				break;
			minor_mat.set_value(data[i][j], r, c);
			c++;
			if (c == 4) {
				c = 0;
				r++;
			}
		}
	}

	return minor_mat.determinant() * pow(-1, row_index + col_index);
}

mat4 mat4::algebraic_additions_mat4() {
	std::vector<float> algebraic_additions_vector{ algebraic_addition(0, 0), algebraic_addition(0, 1), algebraic_addition(0, 2), algebraic_addition(0, 3),
					algebraic_addition(1, 0), algebraic_addition(1, 1), algebraic_addition(1, 2), algebraic_addition(1, 3), algebraic_addition(2, 0),
					algebraic_addition(2, 1), algebraic_addition(2, 2), algebraic_addition(2, 3), algebraic_addition(3, 0),
					algebraic_addition(3, 1), algebraic_addition(3, 2), algebraic_addition(3, 3) };
	return { algebraic_additions_vector };
}

mat4 mat4::reverse_mat4() {
	return  algebraic_additions_mat4().transposed_mat4() * (1 / determinant());
}

bool mat4::operator==(mat4 _mat) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (data[i][j] != _mat.data[i][j]) {
				return false;
			}
		}
	}

	return true;
}
bool mat4::operator!=(mat4 _mat) {
	return !(*this == _mat);
}

mat4 unit_mat4() {
	mat4 unit_mat4;
	unit_mat4.set_value(1, 0, 0);
	unit_mat4.set_value(1, 1, 1);
	unit_mat4.set_value(1, 2, 2);
	unit_mat4.set_value(1, 3, 3);
	return unit_mat4;
}

mat4 translate(vec3& translate_vec) {
	mat4 off_mat4;
	off_mat4.set_value(1, 0, 0);
	off_mat4.set_value(1, 1, 1);
	off_mat4.set_value(1, 2, 2);
	off_mat4.set_value(1, 3, 3);
	off_mat4.set_value(translate_vec.get_a1(), 0, 3);
	off_mat4.set_value(translate_vec.get_a2(), 1, 3);
	off_mat4.set_value(translate_vec.get_a3(), 2, 3);
	return off_mat4;
}

mat4 scale(vec3& scale_vec) {
	mat4 zoom_mat4;
	zoom_mat4.set_value(scale_vec.get_a1(), 0, 0);
	zoom_mat4.set_value(scale_vec.get_a2(), 1, 1);
	zoom_mat4.set_value(scale_vec.get_a3(), 2, 2);
	zoom_mat4.set_value(1, 3, 3);
	return zoom_mat4;
}

mat4 rotate(float angle, const  vec3& arbitrary_axis) {
	mat4 rotate_mat4;

	auto c = (1 - cos(angle));
	rotate_mat4.set_value(cos(angle) + pow(arbitrary_axis.get_a1(), 2) * c, 0, 0);
	rotate_mat4.set_value(arbitrary_axis.get_a1() * arbitrary_axis.get_a2() * c - arbitrary_axis.get_a3() * sin(angle), 0, 1);
	rotate_mat4.set_value(arbitrary_axis.get_a1() * arbitrary_axis.get_a3() * c + arbitrary_axis.get_a2() * sin(angle), 0, 2);

	rotate_mat4.set_value(arbitrary_axis.get_a2() * arbitrary_axis.get_a1() * c + arbitrary_axis.get_a3() * sin(angle), 1, 0);
	rotate_mat4.set_value(cos(angle) + pow(arbitrary_axis.get_a2(), 2) * c, 1, 1);
	rotate_mat4.set_value(arbitrary_axis.get_a2() * arbitrary_axis.get_a3() * c - arbitrary_axis.get_a1() * sin(angle), 1, 2);

	rotate_mat4.set_value(arbitrary_axis.get_a3() * arbitrary_axis.get_a1() * c - arbitrary_axis.get_a2() * sin(angle), 2, 0);
	rotate_mat4.set_value(arbitrary_axis.get_a3() * arbitrary_axis.get_a2() * c + arbitrary_axis.get_a1() * sin(angle), 2, 1);
	rotate_mat4.set_value(cos(angle) + pow(arbitrary_axis.get_a3(), 2) * c, 2, 2);
	rotate_mat4.set_value(1, 3, 3);

	return rotate_mat4;

}

mat4 look_at( vec3& camera_position, vec3& goal_coordinates, vec3& world_up) {
	//vec3 camera_direction = (camera_position - goal_coordinates).normal();
	//vec3 up = world_up.normal();
	//vec3 camera_right = camera_direction.vector_product(up).normal();
	//up = camera_right.vector_product(camera_direction);
	//vec3 camera_right = world_up.vector_product(camera_direction).normal();
	//vec3 up = camera_direction.vector_product(camera_right).normal();

	vec3 camera_direction = (camera_position - goal_coordinates).normal();
	vec3 up = world_up;
	vec3 camera_right = up.vector_product(camera_direction).normal();
	up = camera_direction.vector_product(camera_right).normal();

	mat4 first_mat(0.0f);
	first_mat.set_value(camera_right.get_a1(), 0, 0);
	first_mat.set_value(camera_right.get_a2(), 0, 1);
	first_mat.set_value(camera_right.get_a3(), 0, 2);

	first_mat.set_value(up.get_a1(), 1, 0);
	first_mat.set_value(up.get_a2(), 1, 1);
	first_mat.set_value(up.get_a3(), 1, 2);
	first_mat.set_value(camera_direction.get_a1(), 2, 0);
	first_mat.set_value(camera_direction.get_a2(), 2, 1);
	first_mat.set_value(camera_direction.get_a3(), 2, 2);

	first_mat.set_value(-camera_position.get_a1(), 3, 0);
	first_mat.set_value(-camera_position.get_a2(), 3, 1);
	first_mat.set_value(-camera_position.get_a3(), 3, 2);
	first_mat.set_value(1, 3, 3);

	/*mat4 second_mat(0.0f);

	second_mat.set_value(1, 0, 0);
	second_mat.set_value(1, 1, 1);
	second_mat.set_value(1, 2, 2);
	second_mat.set_value(1, 3, 3);
	second_mat.set_value(-camera_position.get_a1(), 0, 3);
	second_mat.set_value(-camera_position.get_a2(), 1, 3);
	second_mat.set_value(-camera_position.get_a3(), 2, 3);

	auto res_mat = first_mat * second_mat;*/
	return first_mat;
}

mat4 perspective(float fow, float ratio, float near, float far) {
	float tan_fow =  tan(fow / 2.0f);
	auto a = 1.0f / (ratio * tan_fow);
	mat4 perspective_mat;
	perspective_mat.set_value(1.0f / (ratio * tan_fow), 0, 0);
	perspective_mat.set_value(1.0f / (tan_fow), 1, 1);
	perspective_mat.set_value(- (float)(near + far) / (float)(far - near), 2, 2);
	perspective_mat.set_value((2 * far * near) / (near - far), 2, 3);
	perspective_mat.set_value(-1.0f, 3, 2);

	return perspective_mat;
}

mat4 ortho(float left, float right, float bottom, float top, float near, float far) {
	mat4 ortho_mat;
	ortho_mat.set_value(2.0f / (right - left), 0, 0);
	ortho_mat.set_value(- (right + left) / (right - left), 0, 3);
	ortho_mat.set_value(2.0f / (top - bottom), 1, 1);
	ortho_mat.set_value(-(top + bottom) / (top - bottom), 1, 3);
	ortho_mat.set_value(-2.0f / (far - near), 2, 2);
	ortho_mat.set_value(- (far + near) / (far - near), 2, 3);

	ortho_mat.set_value(1.0f, 3, 3);

	return ortho_mat;
}
