#include "vec2.h"
#include<cmath>


vec2::vec2()
	:
	a1(0),
	a2(0) {}

vec2::vec2(float _a1)
	:
	a1(_a1),
	a2(0) {}

vec2::vec2(float _a1, float _a2)
	:
	a1(_a1),
	a2(_a2) {}


void vec2::set_a1(float _a1) {
	a1 = _a1;
}

float vec2::get_a1() {
	return a1;
}

void vec2::set_a2(float _a2) {
	a2 = _a2;
}

float vec2::get_a2() {
	return a2;
}


vec2 vec2::operator+(const vec2& _vec) {
	return { a1 + _vec.a1, a2 + _vec.a2 };
}

vec2 vec2::operator-(const vec2& _vec) {
	return { a1 - _vec.a1, a2 - _vec.a2 };
}

vec2 vec2::operator*(float _number) {
	return { a1 * _number, a2 * _number };
}

vec2 vec2::operator/(float _number) {
	return { a1 / _number, a2 / _number };
}

float vec2::lenght() {
	return sqrt(pow(a1, 2) + pow(a2, 2));
}

vec2 vec2::normal() {
	return { a1 / lenght(), a2 / lenght() };
}

bool vec2::operator==(const vec2& _vec) {
	return a1 == _vec.a1 && a2 == _vec.a2;
}
bool vec2::operator!=(const vec2& _vec) {
	return !(*this == _vec);
}
