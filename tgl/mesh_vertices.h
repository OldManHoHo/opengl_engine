#pragma once
#ifndef TGL_MESHVERTICES_H_
#define TGL_MESHVERTICES_H_

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "tgl/tgl_gl.h"

namespace tgl
{

class MeshVertices
{
	
public:
	GLuint vertex_VBO;
	GLuint normal_VBO;
	GLuint count;


	MeshVertices(std::vector<GLfloat> const &vertices);
	~MeshVertices();
	void calculate_normals(std::vector<GLfloat> const &vertices);
};

} // namespace tgl

#endif
