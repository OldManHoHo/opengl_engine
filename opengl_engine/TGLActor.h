#pragma once
#ifndef TGL_ACTOR_H_
#define TGL_ACTOR_H_

#include <deque>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TGLBounds.h"
#include "TGLComponent.h"

class TGLActor
{
	static int _id_counter;

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
	int id;
    int type;
	
	
// NETWORK
	std::vector <double*> double_props;
	std::vector <float*> float_props;
	std::vector <char*> char_props;
	std::vector <int*> int_props;
	std::vector <glm::vec3*> vec3_props;
	std::vector <glm::mat4*> mat4_props;
	
	std::vector <double*> prev_double_props;
	std::vector <float*> prev_float_props;
	std::vector <char*> prev_char_props;
	std::vector <int*> prev_int_props;
	std::vector <glm::vec3*> prev_vec3_props;
	std::vector <glm::mat4*> prev_mat4_props;
	
	std::deque <void*> network_messsages;
// END NETWORK
	

	TGLBounds * bounds;

	bool transform_calculated;
	bool update_transform;
	bool on_ground;
	friend class TGLPhysicsEngine;
    friend class TGLBase;

public:
	//flags
	bool static_physics;
	bool is_chunk;

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
	

	void register_network_property(double * in_prop);
	void register_network_property(float * in_prop);
	void register_network_property(char * in_prop);
	void register_network_property(int * in_prop);
	void register_network_property(unsigned int * in_prop);
	
	void queue_network_message(void * in_message);
};


#endif