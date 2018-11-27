#pragma once
#ifndef _TGL_TEXTURE
#define _TGL_TEXTURE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class TGLTexture
{
	static GLuint texture_count;
	
	int nrChannels;
	GLuint texture;

public:
	int width;
	int height;

	GLuint texture_id;
	TGLTexture(char * filename);
	~TGLTexture();
	GLuint get_name();

};

#endif