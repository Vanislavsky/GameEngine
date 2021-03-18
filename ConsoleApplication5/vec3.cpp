#include "vec3.h"
#include<cmath>


vec3::vec3()
	:
	a1(0),
	a2(0),
	a3(0) {}

vec3::vec3(float _a1)
	:
	a1(_a1),
	a2(0),
	a3(0) {}

vec3::vec3(float _a1, float _a2, float _a3)
	:
	a1(_a1),
	a2(_a2),
	a3(_a3) {}


void vec3::set_a1(float _a1) {
	a1 = _a1;
}

float vec3::get_a1() {
	return a1;
}

void vec3::set_a2(float _a2) {
	a2 = _a2;
}

float vec3::get_a2() {
	return a2;
}

void vec3::set_a3(float _a3) {
	a3 = _a3;
}

float vec3::get_a3() {
	return a3;
}


vec3 vec3::operator+(const vec3& _vec) {
	return { a1 + _vec.a1, a2 + _vec.a2, a3 + _vec.a3 };
}

vec3 vec3::operator-(const vec3& _vec) {
	return { a1 - _vec.a1, a2 - _vec.a2, a3 - _vec.a3 };
}

vec3 vec3::operator*(float _number) {
	return { a1 * _number, a2 * _number, a3 * _number };
}

vec3 vec3::operator/(float _number) {
	return { a1 / _number, a2 / _number, a3 / _number };
}

float vec3::lenght() {
	return sqrt(pow(a1, 2) + pow(a2, 2) + pow(a3, 2));
}

vec3 vec3::normal() {
	return { a1 / lenght(), a2 / lenght(), a3 / lenght() };
}

vec3 vec3::vector_product(const vec3& _vec) {
	return { a2 * _vec.a3 - a3 * _vec.a2, -(a1 * _vec.a3 - a3 * _vec.a1), a1 * _vec.a2 - a2 * _vec.a1 };
}

bool vec3::operator==(const vec3& _vec) {
	return a1 == _vec.a1 && a2 == _vec.a2 && a3 == _vec.a3;
}
bool vec3::operator!=(const vec3& _vec) {
	return !(*this == _vec);
}
