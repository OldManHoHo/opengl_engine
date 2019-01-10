#include "tgl/actor.h"

namespace tgl
{

int Actor::_id_counter = 0;

Actor::Actor():
	id(_id_counter),
	is_chunk(false)
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


Actor::~Actor()
{
	for (auto c : components)
	{
		delete c;
	}
}

Actor::Actor(const Actor& rhs)
{
	for (auto component : rhs.components)
	{
		//components
	}
}

Actor& Actor::operator=(const Actor& rhs)
{
		
}

void Actor::set_transform(glm::mat4 in_transform)
{
	transform = in_transform;
}

glm::mat4 Actor::get_transform()
{
	if ((transform_calculated != true || static_physics == false))
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

glm::vec3 Actor::get_pos()
{
	return pos;
}

void Actor::set_pos(glm::vec3 in_pos)
{
	pos = in_pos;
	transform_calculated = false;
}

glm::mat4 Actor::get_rot()
{
	return rot;
}

void Actor::set_rot(glm::mat4 in_rot)
{
	rot = in_rot;
	transform_calculated = false;
}

glm::vec3 Actor::get_scale()
{
	return scale;
}

void Actor::set_scale(glm::vec3 in_scale)
{
	scale = in_scale;
}

void Actor::add_component(tgl::Component * in_component)
{
	in_component->parent = this;
	components.push_back(in_component);
}

std::vector <tgl::Component*> Actor::get_components()
{
	return components;
}

void Actor::tick(double time_delta)
{

}

void Actor::translate(glm::vec3 in_translation)
{
	pos += in_translation;
	transform_calculated = false;
}

void Actor::rotate(float angle, glm::vec3 axis)
{
	rot = glm::rotate(rot, angle, axis);
	transform_calculated = false;
}

void Actor::set_bounds(Bounds * in_bounds)
{
	bounds = in_bounds;
}

Bounds * Actor::get_bounds()
{
	return bounds;
}

void Actor::set_on_ground(bool in_on_ground)
{
	on_ground = in_on_ground;
}

bool Actor::get_on_ground()
{
	return on_ground;
}

void Actor::register_network_property(double * in_prop)
{
	//double_props.push_back(in_prop);
	//prev_double_props.push_back(*in_prop);
}

void Actor::queue_network_message(void * in_message)
{
//	network_messsages.push_back(in_message);
}

} // namespace tgl