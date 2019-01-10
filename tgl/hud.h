#pragma once
#ifndef TGL_HUD_H_
#define TGL_HUD_H_

#include "ft2build.h"
#include FT_FREETYPE_H
#include "tgl/base.h"

namespace tgl
{

struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};



class TGLHud
{
	std::map<GLchar, Character> Characters;
	GLuint VAO, VBO;
	GLuint texture;
	std::vector <tgl::Shader *> shaders;
	GLuint shader_program;
public:
	TGLHud();
	~TGLHud();

	void draw();
	void add_shader(tgl::Shader * in_shader);
	GLuint link_shader();
};

} // namespace tgl

#endif