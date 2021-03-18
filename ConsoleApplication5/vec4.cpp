#include "vec4.h"
#include<cmath>


vec4::vec4()
	:
	a1(0),
	a2(0),
	a3(0),
	a4(0) {}

vec4::vec4(float _a1)
	:
	a1(_a1),
	a2(0),
	a3(0),
	a4(0) {}

vec4::vec4(float _a1, float _a2, float _a3, float _a4)
	:
	a1(_a1),
	a2(_a2),
	a3(_a3),
	a4(_a4) {}


void vec4::set_a1(float _a1) {
	a1 = _a1;
}

float vec4::get_a1() {
	return a1;
}

void vec4::set_a2(float _a2) {
	a2 = _a2;
}

float vec4::get_a2() {
	return a2;
}

void vec4::set_a3(float _a3) {
	a3 = _a3;
}

float vec4::get_a3() {
	return a3;
}

void vec4::set_a4(float _a4) {
	a4 = _a4;
}

float vec4::get_a4() {
	return a4;
}


vec4 vec4::operator+(const vec4& _vec) {
	return { a1 + _vec.a1, a2 + _vec.a2, a3 + _vec.a3, a4 + _vec.a4 };
}

vec4 vec4::operator-(const vec4& _vec) {
	return { a1 - _vec.a1, a2 - _vec.a2, a3 - _vec.a3, a4 - _vec.a4 };
}

vec4 vec4::operator*(float _number) {
	return { a1 * _number, a2 * _number, a3 * _number, a4 * _number };
}

vec4 vec4::operator/(float _number) {
	return { a1 / _number, a2 / _number, a3 / _number, a4 / _number };
}

float vec4::lenght() {
	return sqrt(pow(a1, 2) + pow(a2, 2) + pow(a3, 2) + pow(a4, 2));
}

vec4 vec4::normal() {
	return { a1 / lenght(), a2 / lenght(), a3 / lenght(), a4 / lenght() };
}

bool vec4::operator==(const vec4& _vec) {
	return a1 == _vec.a1 && a2 == _vec.a2 && a3 == _vec.a3 && a4 == _vec.a4;
}
bool vec4::operator!=(const vec4& _vec) {
	return !(*this == _vec);
}
