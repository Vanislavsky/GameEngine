#include "light_source.h"


light_source::light_source(light_caster_type _type) {
	type = _type;
}

light_source::light_source(light_caster_type _type, const vec3& _dir, const vec3& _ambient,
	const vec3& _diffuse, const vec3& _specular)
	:
	type(_type),
	direction(_dir),
	ambient(_ambient),
	diffuse(_diffuse),
	specular(_specular) {}

light_source::light_source(light_caster_type _type, const vec3& _pos, const vec3& _ambient,
	const vec3& _diffuse, const vec3& _specular, float _constant, float _linear, float _quadratic)
	:
	type(_type),
	position(_pos),
	ambient(_ambient),
	diffuse(_diffuse),
	specular(_specular),
	constant(_constant),
	linear(_linear),
	quadratic(_quadratic) {}

light_source::light_source(light_caster_type _type, const vec3& _pos, const vec3& _dir, const vec3& _ambient,
	const vec3& _diffuse, const vec3& _specular, float _constant, float _linear, float _quadratic, float _cutOff, float _outerCutOff)
	:
	type(_type),
	position(_pos),
	direction(_dir),
	ambient(_ambient),
	diffuse(_diffuse),
	specular(_specular),
	constant(_constant),
	linear(_linear),
	quadratic(_quadratic),
	cutOff(_cutOff),
	outerCutOff(_outerCutOff) {}

light_source::light_caster_type light_source::get_type() {
	return type;
}

void light_source::set_direction(const vec3& _direction) {
	direction = _direction;
}
vec3 light_source::get_direction() {
	return direction;
}

void light_source::set_ambient(const vec3& _ambient) {
	ambient = _ambient;
}
vec3 light_source::get_ambient() {
	return ambient;
}

void light_source::set_diffuse(const vec3& _diffuse) {
	diffuse = _diffuse;
}
vec3 light_source::get_diffuse() {
	return diffuse;
}

void light_source::set_specular(const vec3& _specular) {
	specular = _specular;
}
vec3 light_source::get_specular() {
	return specular;
}

void light_source::set_position(const vec3& _pos) {
	position = _pos;
}

vec3 light_source::get_position() {
	return position;
}

void light_source::set_constant(float _constant) {
	constant = _constant;
}
float light_source::get_constant() {
	return constant;
}

void light_source::set_linear(float _linear) {
	linear = _linear;
}
float light_source::get_linear() {
	return linear;
}

void light_source::set_quadratic(float _quadratic) {
	quadratic = _quadratic;
}
float light_source::get_quadratic() {
	return quadratic;
}

void light_source::set_cutOff(float _cutOff) {
	cutOff = _cutOff;
}

float light_source::get_cutOff() {
	return cutOff;
}

void light_source::set_outerCutOff(float _outerCutOff) {
	outerCutOff = _outerCutOff;
}
float light_source::get_outerCutOff() {
	return outerCutOff;
}