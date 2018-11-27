#pragma once
#ifndef _TGL_CHUNKSPAWN
#define _TGL_CHUNKSPAWN

#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "TGLActor.h"
#include "TGLChunk.h"
#include "TGLMesh.h"
#include "BlockGenerator.h"

struct face_map_pair
{
	int normal;
	int x;
	int y;
};

typedef double hit_properties;

struct block_hit
{
	glm::vec3 loc;
	hit_properties props;
}

class TGLChunkSpawn : public TGLActor
{
	std::map <chunk_coord, TGLChunk*> chunks;

	TGLMeshVertices * block_mesh_vertices;
	TGLTexture * block_texture;
	TGLMaterial * block_material;

	BlockGenerator * block_generator;

	int block_type_count;

	std::vector <TGLMesh*> meshes;
	std::vector <chunk_coord> chunks_to_load;
	
	std::deque <block_hit> posted_hits;
	static const unsigned int hits_to_break = 1;
	std::deque <block_def> posted_placements;

	bool test_chunk;
	e_block_type pointed_at;

public:

	TGLChunkSpawn();

	glm::vec3 get_block_pointed_at(glm::vec3 origin, glm::vec3 pointing_vector, double max_distance = 5.0, e_block_type& out_block_type = pointed_at)

	void tick(double time_delta);

	void spawn_chunk(int chunk_x, int chunk_y);

	std::vector <GLfloat> create_uv_map(std::vector <face_map_pair> pairs);

	bool TGLChunkSpawn::between_angles(float x, float y, float in_angle_1, float in_angle_2);

	std::vector <chunk_coord> TGLChunkSpawn::get_chunks(int x0, int y0, int radius, float view_angle_1, float view_angle_2);

	e_block_type get_point(int x, int y, int z);

	e_block_type * get_points(int x, int y, int division);
	
	void get_chunk_of_point(glm::vec3 in_point, int& out_chunk_x, int& out_chunk_y);
	
	void post_hit(block_hit in_hit);
	
	void post_placement(glm::vec3 in_loc, e_block_type in_type);
	
	glm::vec3 get_block_pointed_at()
};

#endif