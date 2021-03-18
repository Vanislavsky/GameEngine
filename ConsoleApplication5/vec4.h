#pragma once

class vec4
{
public:
	vec4();
	vec4(float);
	vec4(float, float, float, float);

	float get_a1();
	float get_a2();
	float get_a3();
	float get_a4();
	void set_a1(float);
	void set_a2(float);
	void set_a3(float);
	void set_a4(float);


	vec4 operator+(const vec4&);
	vec4 operator-(const vec4&);
	vec4 operator*(float);
	vec4 operator/(float);

	float lenght();
	vec4 normal();

	bool operator==(const vec4&);
	bool operator!=(const vec4&);
private:
	float a1;
	float a2;
	float a3;
	float a4;
};

