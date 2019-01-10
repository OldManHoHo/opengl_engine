#pragma once
#ifndef TGL_CAMERA_H_
#define TGL_CAMERA_H_

#include "tgl/actor.h"

namespace tgl
{

class Camera : public tgl::Actor
{

	glm::mat4 projection;
	glm::mat4 view;

public:
	glm::vec3 eye_loc;
	Camera();
	~Camera();
	void set_projection(glm::mat4 in_mat);
	glm::mat4 get_projection();
	glm::mat4 get_view();
	void set_view(glm::mat4 in_view);
	void tick(double time_delta);
};

} // namespace tgl

#endif