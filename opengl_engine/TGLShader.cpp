#include "TGLShader.h"

#include <iostream>
#include <fstream>
#include <streambuf>

TGLShader::TGLShader(char * shader_file, GLuint shader_type)
{
	load_shader(shader_file, shader_type);
}


TGLShader::~TGLShader()
{
}

void TGLShader::load_shader(char * shader_file, GLuint shader_type)
{
	int  success;
	char infoLog[512];

	std::ifstream t(shader_file);
	std::string str;

	t.seekg(0, std::ios::end);
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	const GLchar *source = (const GLchar *)str.c_str();
	printf(source);
	shader_object = glCreateShader(shader_type);

	glShaderSource(shader_object, 1, &source, NULL);
	glCompileShader(shader_object);

	
	glGetShaderiv(shader_object, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader_object, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

GLuint TGLShader::get_shader_name()
{
	return shader_object;
}