#include "TGLCamera.h"
#include <iostream>



TGLCamera::TGLCamera()
{
	//projection = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);
	translate(glm::vec3(10.0, 180.0, 10.0));
	//set_transform(glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f),
	//	glm::vec3(0.0f, 0.0f, 0.0f),
	//	glm::vec3(0.0f, 1.0f, 0.0f)));
}

TGLCamera::~TGLCamera()
{
}

void TGLCamera::set_projection(glm::mat4 in_mat)
{
	projection = in_mat;
}

glm::mat4 TGLCamera::get_projection()
{
	return projection;
}

glm::mat4 TGLCamera::get_view()
{
	glm::vec3 forward(1.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	forward = glm::mat3(get_rot())*forward;
	up = glm::mat3(get_rot())*up;
	eye_loc = get_pos() + up*float(1.65 - 1.85 / 2);
	view = glm::lookAt(eye_loc, eye_loc + forward, up);
	return view;
}

void TGLCamera::set_view(glm::mat4 in_view)
{
	view = in_view;
}

void TGLCamera::tick(double time_delta)
{

}
