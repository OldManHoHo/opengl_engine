#pragma once
#ifndef TGL_MATERIAL_H_
#define TGL_MATERIAL_H_

#include <vector>

#include "tgl/shader.h"
#include "tgl/texture.h"

namespace tgl
{

class Material
{
	std::vector <tgl::Texture *> textures;
	std::vector <tgl::Shader *> shaders;
	std::vector <GLuint> uv_VBOs;

	GLuint shader_program;

	

public:
	bool wireframe;
	bool linked;
	bool default_program;

	Material();
	~Material();
	void add_shader(tgl::Shader * in_shader);
	void add_texture(tgl::Texture * in_texture, GLfloat * in_coords, int coord_length);
	GLuint link_shader();
	GLuint get_shader_program();
	std::vector <tgl::Texture*> get_textures();
	GLuint get_uv_VBO(int uv_index);
};

} // namespace tgl

#endif