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

enum e_block_type
{
	bt_air,
	bt_dirt_with_grass,
	bt_dirt,
	bt_stone,
	bt_tree,
	bt_leaves,
	bt_water,
	bt_sand,
	bt_invalid
};


struct chunk_coord
{
	chunk_coord(int in_x, int in_y) { x = in_x; y = in_y; }
	int x;
	int y;
	const bool operator < (const chunk_coord &r) const {
		return (x < r.x) || (x == r.x && y < r.y);
	}
	const bool operator == (const chunk_coord &r) const {
		return x == r.x && y == r.y;
	}
};

struct block_coord
{
	block_coord() {}
	block_coord(glm::vec3 in_vec) {x = in_vec.x; y = in_vec.y; z = in_vec.z;}
	block_coord(int in_x, int in_y, int in_z) {
		x = in_x; y = in_y; z = in_z;
	}
	bool operator==(const block_coord& in_coord)
	{
		return (in_coord.x == x && in_coord.y == y && in_coord.z == z);
	}

	const bool operator < (const block_coord &r) const {
		return (x < r.x) || (x == r.x && y < r.y) || (x == r.x && y == r.y && z < r.z);
	}

	glm::vec3 get_vec() { return glm::vec3(x, y, z); }
	int x;
	int y;
	int z;
};

struct block_def
{
	block_coord loc;
	e_block_type type;
	block_def() {}
	block_def(int in_x, int in_y, int in_z, e_block_type in_type) :
		loc(in_x, in_y, in_z),
		type(in_type)
	{}

	bool operator== (const block_def& in_def)
	{
		return loc == in_def.loc;
	}

};



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

