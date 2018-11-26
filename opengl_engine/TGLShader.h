#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class TGLShader
{
	GLuint shader_object;

public:
	TGLShader(char * shader_file, GLuint shader_type);
	~TGLShader();

	void load_shader(char * shader_file, GLuint shader_type);
	GLuint get_shader_name();
};

