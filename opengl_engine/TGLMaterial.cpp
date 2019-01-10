#include "TGLMaterial.h"

#include <iostream>
#include <string>


TGLMaterial::TGLMaterial()
{
	wireframe = false;
	linked = false;
	default_program = true;
}


TGLMaterial::~TGLMaterial()
{
}

void TGLMaterial::add_shader(TGLShader * in_shader)
{
	shaders.push_back(in_shader);
	default_program = false;
}

void TGLMaterial::add_texture(TGLTexture * in_texture, GLfloat * in_coords, int coord_length)
{
	
	GLuint vbo;
	glGenBuffers(1, &vbo);
	uv_VBOs.push_back(vbo);
	//glGenVertexArrays(1, &to.VAO);

	//glBindVertexArray(to.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, coord_length * sizeof(GLfloat), in_coords, GL_STATIC_DRAW);
	textures.push_back(in_texture);
	glUseProgram(shader_program);
	std::string tex_name = ("texture" + std::to_string(textures.size() - 1)).c_str();
	GLint tex_loc = glGetUniformLocation(shader_program, tex_name.c_str());
	glUniform1i(tex_loc, textures.size() - 1);
}

GLuint TGLMaterial::link_shader()
{
	int  success;
	char infoLog[512];

	if (shader_program != 0)
	{
		glDeleteProgram(shader_program);
	}

	shader_program = glCreateProgram();

	for (auto it = shaders.begin(); it != shaders.end(); ++it)
	{
		glAttachShader(shader_program, (*it)->get_shader_name());
	}

	glLinkProgram(shader_program);

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
		std::cout << "SHADER LINK FAILED\n" << infoLog << std::endl;
		linked = false;
	}
	else
	{
		linked = true;
	}
	return shader_program;
}

GLuint TGLMaterial::get_shader_program()
{
	return shader_program;
}

std::vector <TGLTexture*> TGLMaterial::get_textures()
{
	return textures;
}

GLuint TGLMaterial::get_uv_VBO(int uv_index)
{
	return uv_VBOs[uv_index];
}