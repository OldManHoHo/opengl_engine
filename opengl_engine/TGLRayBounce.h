#pragma once
#ifndef TGL_RAYBOUNCE_H_
#define TGL_RAYBOUNCE_H_


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "tgl_gl.h"
#include "TGLShader.h"
#include "TGLMaterial.h"

class TGLRayBounce
{

	TGLShader * v_shader;
	TGLShader * f_shader;
	
	int swapper;

public:
	unsigned int shadow_map_size;

	TGLMaterial * mat;
	GLuint depthTexture;
	GLuint depthTexture2;
	GLuint FramebufferName;
	GLuint FramebufferName2;

	TGLRayBounce();
	~TGLRayBounce();
	void init();
	void set_up();
	void swap_buffers();
	GLuint get_texture();
	GLuint get_framebuffer();
};

#endif