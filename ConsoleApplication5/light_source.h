#pragma once

#include"vec3.h"
class light_source
{
public:
	enum light_caster_type {
		DIRLIGHT,
		POINTLIGHT,
		SPOTLIGHT,
	};

	light_source(light_caster_type);
	light_source(light_caster_type, const vec3&, const vec3&, const vec3&, const vec3&);
	light_source(light_caster_type, const vec3&, const vec3&, const vec3&, const vec3&, float, float, float);
	light_source(light_caster_type, const vec3&, const vec3&, const vec3&, const vec3&, const vec3&, float, float, float, float, float);

	light_caster_type get_type();

	void set_direction(const vec3&);
	vec3 get_direction();

	void set_ambient(const vec3&);
	vec3 get_ambient();

	void set_diffuse(const vec3&);
	vec3 get_diffuse();

	void set_specular(const vec3&);
	vec3 get_specular();

	void set_position(const vec3&);
	vec3 get_position();

	void set_constant(float);
	float get_constant();

	void set_linear(float);
	float get_linear();

	void set_quadratic(float);
	float get_quadratic();

	void set_cutOff(float);
	float get_cutOff();

	void set_outerCutOff(float);
	float get_outerCutOff();

private:
	light_caster_type type;

	//направленный свет
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	//точечный источник
	vec3 position;
	float constant;
	float linear;
	float quadratic;

	//прожектор
	float cutOff;
	float outerCutOff;
};

