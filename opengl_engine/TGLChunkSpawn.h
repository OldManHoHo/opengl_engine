#pragma once
#ifndef _TGL_CHUNKSPAWN
#define _TGL_CHUNKSPAWN

#include <map>

#include "tgl_gl.h"

#include <vector>
#include <deque>

#include "TGLActor.h"
#include "TGLChunk.h"
#include "TGLMesh.h"
#include "BlockGenerator.h"
//#include "TMCDroppedItem.h"


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
	e_block_type type;
	hit_properties props;
};

template <class keyClass, class elementClass>
class chunk_searcher
{
	
public:
	std::map <keyClass, std::vector<elementClass>> listing;
	void add_item(elementClass in_item, keyClass key);
	void remove_item(elementClass in_item, keyClass key);
	keyClass find_item(elementClass in_item);

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
	
	std::deque <block_hit> posted_hits;
	static const unsigned int hits_to_break = 1;
	std::deque <block_def> posted_placements;
	//td::unordered_map <chunk_coord, std::vector<TGLActor*>> dropped_items;
	chunk_searcher<chunk_coord, TGLActor*> dropped_items;

	bool test_chunk;
	static e_block_type pointed_at;

public:

	TGLChunkSpawn();

	glm::vec3 get_block_pointed_at(glm::vec3 origin, glm::vec3 pointing_vector, double max_distance, e_block_type& out_block_type, glm::vec3& out_prev_block);
	void tick(double time_delta);
	void spawn_chunk(int chunk_x, int chunk_y);
	void despawn_chunk(int chunk_x, int chunk_y);
	std::vector <GLfloat> create_uv_map(std::vector <face_map_pair> pairs);
	bool between_angles(float x, float y, float in_angle_1, float in_angle_2);
	std::vector <chunk_coord> get_chunks(int x0, int y0, int radius, float view_angle_1, float view_angle_2);
	e_block_type get_point(int x, int y, int z);
	e_block_type * get_points(int x, int y, int division);
	void get_chunk_of_point(glm::vec3 in_point, int& out_chunk_x, int& out_chunk_y);
	void post_hit(block_hit in_hit);
	void post_placement(block_def in_block);
	std::vector <TGLActor*> collect_nearby_dropped_items(glm::vec3 pos, double radius);
	
	void client_request_chunk(int chunk_x, int chunk_y);
	void server_send_chunk_mods(int chunk_x, int chunk_y);
	bool chunk_in_fov(int chunk_x, int chunk_y, glm::vec3 player, glm::vec3 player_forward);

	std::vector <GLshort> TGLChunkSpawn::get_block_light_value(int in_x, int in_y, int in_z);
};

#endif
