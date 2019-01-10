#pragma once
#ifndef TGL_TEXTURE_H_
#define TGL_TEXTURE_H_

#include "tgl_gl.h"

class TGLTexture
{
	static GLuint texture_count;
	
	int nrChannels;
	
public:
	GLuint texture;
	int width;
	int height;

	GLuint texture_id;
	TGLTexture(char * filename);
	~TGLTexture();
	GLuint get_name();

};

#endif
