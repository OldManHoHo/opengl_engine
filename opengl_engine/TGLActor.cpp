#include "TGLActor.h"

int TGLActor::_id_counter = 0;

TGLActor::TGLActor():
	id(_id_counter)
{
	transform = glm::mat4(1.0);
	scale = glm::vec3(1.0, 1.0, 1.0);
	pos = glm::vec3(0, 0, 0);
	//rot = glm::quat(0.0, glm::vec3(0,1.0,0));
	rot = glm::mat4(1.0);
	mass = 20;

	bounds = nullptr;
	on_ground = false;
	static_physics = false;
	transform_calculated = false;
	
	_id_counter += 1;
}


TGLActor::~TGLActor()
{
	for (auto c : components)
	{
		delete c;
	}
}


void TGLActor::set_transform(glm::mat4 in_transform)
{
	transform = in_transform;
}

glm::mat4 TGLActor::get_transform()
{
	if (transform_calculated != true || static_physics == false)
	{
		glm::mat4 out_transform(1.0);
		glm::mat4 trans = glm::translate(out_transform, pos);
		glm::mat4 rotator = rot*out_transform;
		glm::mat4 scaler = glm::scale(out_transform, scale);
		
		transform = out_transform*trans*rotator*scaler;
		transform_calculated = true;
	}

	return transform;
}

glm::vec3 TGLActor::get_pos()
{
	return pos;
}

void TGLActor::set_pos(glm::vec3 in_pos)
{
	pos = in_pos;
	transform_calculated = false;
}

glm::mat4 TGLActor::get_rot()
{
	return rot;
}

void TGLActor::set_rot(glm::mat4 in_rot)
{
	rot = in_rot;
	transform_calculated = false;
}

glm::vec3 TGLActor::get_scale()
{
	return scale;
}

void TGLActor::set_scale(glm::vec3 in_scale)
{
	scale = in_scale;
}

void TGLActor::add_component(TGLComponent * in_component)
{
	in_component->parent = this;
	components.push_back(in_component);
}

std::vector <TGLComponent*> TGLActor::get_components()
{
	return components;
}

void TGLActor::tick(double time_delta)
{

}

void TGLActor::translate(glm::vec3 in_translation)
{
	pos += in_translation;
	transform_calculated = false;
}

void TGLActor::rotate(float angle, glm::vec3 axis)
{
	rot = glm::rotate(rot, angle, axis);
	transform_calculated = false;
}

void TGLActor::set_bounds(TGLBounds * in_bounds)
{
	bounds = in_bounds;
}

TGLBounds * TGLActor::get_bounds()
{
	return bounds;
}

void TGLActor::set_on_ground(bool in_on_ground)
{
	on_ground = in_on_ground;
}

bool TGLActor::get_on_ground()
{
	return on_ground;
}

void TGLActor::register_network_property(double * in_prop)
{
	//double_props.push_back(in_prop);
	//prev_double_props.push_back(*in_prop);
}

void TGLActor::queue_network_message(void * in_message)
{
//	network_messsages.push_back(in_message);
}