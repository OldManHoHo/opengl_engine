#pragma once
#include "tgl_gl.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "TGLShader.h"
#include "TGLMaterial.h"

class TGLRayBounce
{

	TGLShader * v_shader;
	TGLShader * f_shader;
	

public:
	TGLMaterial * mat;
	GLuint depthTexture;
	GLuint FramebufferName;

	TGLRayBounce();
	~TGLRayBounce();
	void init();
	void set_up();
};

