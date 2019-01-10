#pragma once
#ifndef TGL_MESHVERTICES_H_
#define TGL_MESHVERTICES_H_

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "tgl_gl.h"

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
