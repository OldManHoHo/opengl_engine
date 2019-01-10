#pragma once
#ifndef TGL_CHUNK_H_
#define TGL_CHUNK_H_

#include "tgl_gl.h"
#include "TGLActor.h"
#include "TGLMaterial.h"
#include "TGLMeshVertices.h"


class TGLChunk : public TGLActor
{
	std::vector <std::vector <GLfloat>> block_instances;
public:
	//const int x;
	//const int y;
	TGLChunk(TGLMeshVertices * mesh_vertices, TGLMaterial * block_material, int type_count, std::vector <std::vector <GLfloat>> instances);
	~TGLChunk();

	bool remove_instance(int block_type, glm::vec3 loc);
	void add_instance(int block_type, glm::vec3 loc);
};

#endif
