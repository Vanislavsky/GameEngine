#pragma once


class vec3
{
public:
	vec3();
	vec3(float);
	vec3(float, float, float);

	float get_a1();
	float get_a2();
	float get_a3();
	void set_a1(float);
	void set_a2(float);
	void set_a3(float);


	vec3 operator+(const vec3&);
	vec3 operator-(const vec3&);
	vec3 operator*(float);
	vec3 operator/(float);

	float lenght();
	vec3 normal();
	vec3 vector_product(const vec3&);

	bool operator==(const vec3&);
	bool operator!=(const vec3&);
private:
	float a1;
	float a2;
	float a3;
};

