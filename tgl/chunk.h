#pragma once
#ifndef TGL_CHUNK_H_
#define TGL_CHUNK_H_

#include "tgl/tgl_gl.h"
#include "tgl/actor.h"
#include "tgl/material.h"
#include "tgl/mesh_vertices.h"

namespace tmc
{

class Chunk : public tgl::Actor
{
	std::vector <std::vector <GLfloat>> block_instances;
public:
	//const int x;
	//const int y;
	Chunk(tgl::MeshVertices * mesh_vertices, tgl::Material * block_material, int type_count, std::vector <std::vector <GLfloat>> instances);
	~Chunk();

	bool remove_instance(int block_type, glm::vec3 loc);
	void add_instance(int block_type, glm::vec3 loc);
};

} // namespace tmc

#endif
