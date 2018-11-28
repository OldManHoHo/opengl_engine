#pragma once
#ifndef _TGL_SHADER
#define _TGL_SHADER


#include "tgl_gl.h"

class TGLShader
{
	GLuint shader_object;

public:
	TGLShader(char * shader_file, GLuint shader_type);
	~TGLShader();

	void load_shader(char * shader_file, GLuint shader_type);
	GLuint get_shader_name();
};

#endif
