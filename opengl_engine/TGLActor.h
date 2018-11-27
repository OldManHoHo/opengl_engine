#pragma once
#ifndef _TGL_ACTOR
#define _TGL_ACTOR

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "TGLComponent.h"
#include "TGLBounds.h"

class TGLActor
{

protected:
	glm::vec3 pos;
	glm::vec3 prev_pos;
	glm::vec3 vel;
	glm::vec3 accel;
	float mass;
	glm::mat4 rot;
	glm::vec3 scale;
	glm::mat4 transform;
	std::vector <TGLComponent *> components;


	TGLBounds * bounds;

	bool transform_calculated;
	bool on_ground;
	friend class TGLPhysicsEngine;

public:
	//flags
	bool static_physics;

	TGLActor();
	~TGLActor();
	void set_transform(glm::mat4 in_transform);
	glm::mat4 get_transform();
	glm::vec3 get_pos();
	void set_pos(glm::vec3 in_pos);
	glm::mat4 get_rot();
	void set_rot(glm::mat4 in_rot);
	glm::vec3 get_scale();
	void set_scale(glm::vec3 in_scale);
	void add_component(TGLComponent * in_component);
	std::vector <TGLComponent*> get_components();
	virtual void tick(double time_delta);
	void translate(glm::vec3 in_translation);
	void rotate(float angle, glm::vec3 axis);
	void set_bounds(TGLBounds * in_bounds);
	TGLBounds * get_bounds();
	void set_on_ground(bool in_on_ground);
	bool get_on_ground();
};


#endif