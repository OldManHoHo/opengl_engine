#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class TGLTexture
{
	static GLuint texture_count;
	
	GLuint texture;

public:
	GLuint texture_id;
	TGLTexture(char * filename);
	~TGLTexture();
	GLuint get_name();

};

