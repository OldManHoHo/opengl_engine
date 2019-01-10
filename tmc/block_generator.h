#ifndef TMC_BLOCKGENERATOR_H_
#define TMC_BLOCKGENERATOR_H_

// Class BlockGenerator
//
// The BlockGenerator class is intended to generate block types
// based on input of coordinates. Given discrete input of coordinates
// BlockGenerator should return either a number of block types
// in a given space or a single block type for the given coordinate.
//

#pragma once
#include <map>
#include <mutex>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "tmc/cellular.h"
#include "tmc/generator.h"
#include "tmc/simplex.h"
#include "tmc/chunk_database.h"
#include "tmc/coord_types.h"
#include "tmc/white_noise.h"

namespace tmc
{

class BlockGenerator
{
	// Various noise generators for terrain generation
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
	
	// Size of last get_points call
	int size_x;
	int size_y;
	int counter;
	
	int seed;

	bool test_gen;

	// Player made modification storage
	std::map <chunk_coord, std::map<block_coord,block_def>> world_mods;
	
	// Player made modification file storage access
	tmc::ChunkDatabase chunk_db;

	// Single mutex used for access of whole object
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

} // namespace tmc

#endif