#pragma once

#include"vec4.h"
#include"vec3.h"
#include"mat4.h"

class camera {
public:
	enum class ProjectionMode { ORTHOGRAPHIC, PERSPECTIVE};
	
	camera();

	float get_fov() const;
	float fetRatio() const;
	float get_near() const;
	float get_far() const;
	vec3 get_position();
	vec3 get_front();
	vec3 get_up();
	void set_fov(float p_value);
	void set_ratio(float p_value);
	void set_near(float p_value);
	void set_far(float p_value);
	void set_postion(vec3);
	void set_front(vec3);
	void set_up(vec3);

	mat4 get_projection_matrix() const;
	mat4 get_view_matrix();
	mat4 get_model_matrix(float, const vec3&) const;
	mat4 get_translate_matrix(vec3&) const;
public:
	
	vec3 position;
	vec3 front = {0.0, 0.0, 0.0};
	vec3 up = {0.0f, 1.0f, 0.0f};
	vec3 right;
	vec3 world_up;
	float m_fov;
	float m_ratio;
	float m_near;
	float m_far;

	float yaw;
	float pitch;

	void update_canera_vectors();
};
