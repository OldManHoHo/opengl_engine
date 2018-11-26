#pragma once
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

	bool test_chunk;

public:

	TGLChunkSpawn();

	void tick(double time_delta);

	void spawn_chunk(int chunk_x, int chunk_y);

	std::vector <GLfloat> create_uv_map(std::vector <face_map_pair> pairs);

	bool TGLChunkSpawn::between_angles(float x, float y, float in_angle_1, float in_angle_2);

	std::vector <chunk_coord> TGLChunkSpawn::get_chunks(int x0, int y0, int radius, float view_angle_1, float view_angle_2);

	int get_point(int x, int y, int z);

	unsigned char * get_points(int x, int y, int division);
};