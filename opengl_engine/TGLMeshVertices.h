#pragma once
#ifndef _TGL_MESHVERTICES
#define _TGL_MESHVERTICES

#include "tgl_gl.h"

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TGLMeshVertices
{
	
public:
	GLuint vertex_VBO;
	GLuint normal_VBO;
	GLuint count;


	TGLMeshVertices(std::vector<GLfloat> const &vertices);
	~TGLMeshVertices();
	void calculate_normals(std::vector<GLfloat> const &vertices);
};

#endif
