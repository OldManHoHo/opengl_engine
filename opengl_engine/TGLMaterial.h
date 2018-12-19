#pragma once
#ifndef _TGL_MATERIAL
#define _TGL_MATERIAL

#include <vector>

#include "TGLTexture.h"
#include "TGLShader.h"

class TGLMaterial
{
	std::vector <TGLTexture *> textures;
	std::vector <TGLShader *> shaders;
	std::vector <GLuint> uv_VBOs;

	GLuint shader_program;

	

public:
	bool wireframe;
	bool linked;
	bool default_program;

	TGLMaterial();
	~TGLMaterial();
	void add_shader(TGLShader * in_shader);
	void add_texture(TGLTexture * in_texture, GLfloat * in_coords, int coord_length);
	GLuint link_shader();
	GLuint get_shader_program();
	std::vector <TGLTexture*> get_textures();
	GLuint get_uv_VBO(int uv_index);
};

#endif