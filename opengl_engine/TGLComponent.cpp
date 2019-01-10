#include <stdio.h>

#include "TGLActor.h"
#include "TGLComponent.h"


TGLComponent::TGLComponent() : parent(nullptr), is_child(false)
	
{
	transform = glm::mat4(1.0);
	
	scale = glm::vec3(1.0, 1.0, 1.0);
	pos = glm::vec3(0, 0, 0);
	rot = glm::quat();

	draw_flag = false;
	transform_calculated = false;
}


TGLComponent::~TGLComponent()
{
}

void TGLComponent::set_transform(glm::mat4 in_transform)
{
	transform = in_transform;
	transform_calculated = true;
}

glm::mat4 TGLComponent::get_transform()
{


	if (transform_calculated != true)
	{
		glm::mat4 out_transform(1.0);


		out_transform = glm::scale(out_transform, scale);
		out_transform = glm::mat4_cast(rot)*out_transform;
		out_transform = glm::translate(out_transform, pos);

		if (parent != nullptr && is_child)
		{
			//out_transform = glm::scale(out_transform, parent->get_scale());
			
			//out_transform = glm::translate(out_transform, parent->get_pos());
			//out_transform = glm::mat4_cast(parent->get_rot())*out_transform;
		}

		transform = out_transform;
		transform_calculated = true;
	}

	return transform;
}

bool TGLComponent::get_draw_flag()
{
	return draw_flag;
}

void TGLComponent::translate(glm::vec3 in_translation)
{
	pos += in_translation;
	transform_calculated = false;
}

void TGLComponent::set_rot(glm::quat in_rot)
{
	rot = in_rot;
	transform_calculated = false;
}

void TGLComponent::rotate(float angle, glm::vec3 axis)
{
	rot = glm::rotate(rot, angle, axis);
	transform_calculated = false;
}

void TGLComponent::set_pos(glm::vec3 in_pos)
{
	pos = in_pos;
	transform_calculated = false;
}