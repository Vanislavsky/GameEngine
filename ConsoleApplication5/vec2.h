#pragma once

class vec2
{
public:
	vec2();
	vec2(float);
	vec2(float, float);

	float get_a1();
	float get_a2();
	void set_a1(float);
	void set_a2(float);


	vec2 operator+(const vec2&);
	vec2 operator-(const vec2&);
	vec2 operator*(float);
	vec2 operator/(float);

	float lenght();
	vec2 normal();

	bool operator==(const vec2&);
	bool operator!=(const vec2&);
protected:
	float a1;
	float a2;
};

