#pragma once

#ifndef _TGL_CAMERA
#define _TGL_CAMERA

#include "TGLActor.h"

class TGLCamera : public TGLActor
{

	glm::mat4 projection;
	glm::mat4 view;

public:
	TGLCamera();
	~TGLCamera();
	void set_projection(glm::mat4 in_mat);
	glm::mat4 get_projection();
	glm::mat4 get_view();
	void set_view(glm::mat4 in_view);
	void tick(double time_delta);
};

#endif