#pragma once
#ifndef TGL_RAYBOUNCE_H_
#define TGL_RAYBOUNCE_H_


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "tgl/tgl_gl.h"
#include "tgl/tgl::Shader.h"
#include "tgl/tgl::Material.h"

namespace tgl
{

class RayBounce
{

	tgl::Shader * v_shader;
	tgl::Shader * f_shader;
	
	int swapper;

public:
	unsigned int shadow_map_size;

	tgl::Material * mat;
	GLuint depthTexture;
	GLuint depthTexture2;
	GLuint FramebufferName;
	GLuint FramebufferName2;

	RayBounce();
	~RayBounce();
	void init();
	void set_up();
	void swap_buffers();
	GLuint get_texture();
	GLuint get_framebuffer();
};

} // namespace tgl

#endif