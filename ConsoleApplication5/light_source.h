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

private:
	light_caster_type type;

	//������������ ����
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	//�������� ��������
	float constant;
	float linear;
	float quadratic;

	//���������
	float cutOff;
	float outerCutOff;
};

