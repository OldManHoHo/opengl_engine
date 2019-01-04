#pragma once
#include <map>
#include <vector>
#include <mutex>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Generator.h"
#include "Simplex.h"
#include "Cellular.h"
#include "WhiteNoise.h"
#include "TMCChunkDatabase.h"
#include "TMCCoordTypes.h"

class BlockGenerator
{
	Simplex * height;
	Simplex * height2;
	Simplex * height3;
	Simplex * height4;
	Simplex * height5;
	Simplex * mountains;
	Simplex * mountains2;
	WhiteNoise * trees;
	Simplex * caves;
	Simplex * caves2;
	e_block_type * blocks;
	int size_x;
	int size_y;
	int counter;
	int seed;

	bool test_gen;

	std::map <chunk_coord, std::map<block_coord,block_def>> world_mods;
	TMCChunkDatabase chunk_db;

	std::recursive_mutex access_mutex;

public:
	//BlockStore block_file;

public:


	BlockGenerator(bool tester = false);
	~BlockGenerator();

	e_block_type get_point(int in_x, int in_y, int in_z);
	e_block_type get_point_2d(int in_x, int in_y);
	e_block_type * get_points(int in_x, int in_y, int in_z, int division);
	e_block_type * get_points_2d(int in_x, int in_y, int division);
	void set_point(e_block_type block_type, int in_x, int in_y, int in_z);
	e_block_type check_for_mod(int in_x, int in_y, int in_z);
	e_block_type index(int in_x, int in_y, int in_z);
	bool is_visible(int in_x, int in_y, int in_z);
	void get_tree(float * in_noise, e_block_type * in_blocks, int in_x, int in_y, int in_z, int chunk_x = 0, int chunk_y = 0);

};


#ifdef _UNIT_TEST
void BlockGenerator_TEST();
#endif