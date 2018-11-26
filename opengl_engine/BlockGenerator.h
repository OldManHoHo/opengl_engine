#pragma once
#include <map>
#include <vector>

#include "Generator.h"
#include "Simplex.h"
#include "Cellular.h"
#include "WhiteNoise.h"

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
	block_coord(int in_x, int in_y, int in_z) {
		x = in_x; y = in_y; z = in_z;
	}
	bool operator==(const block_coord& in_coord)
	{
		return (in_coord.x == x && in_coord.y == y && in_coord.z == z);
	}
	int x;
	int y;
	int z;
};

struct block_def
{
	block_coord loc;
	int type;
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
	unsigned char * blocks;
	int size_x;
	int size_y;
	int counter;
	int seed;

	bool test_gen;

	std::map <chunk_coord, std::vector<block_def>> world_mods;

public:
	//BlockStore block_file;

public:


	BlockGenerator(bool tester = false);
	~BlockGenerator();

	unsigned char get_point(int in_x, int in_y, int in_z);
	unsigned char get_point_2d(int in_x, int in_y);
	unsigned char * get_points(int in_x, int in_y, int in_z, int division);
	unsigned char * get_points_2d(int in_x, int in_y, int division);
	void set_point(int block_type, int in_x, int in_y, int in_z);
	int check_for_mod(int in_x, int in_y, int in_z);
	unsigned char index(int in_x, int in_y, int in_z);
	bool is_visible(int in_x, int in_y, int in_z);
	void get_tree(float * in_noise, unsigned char * in_blocks, int in_x, int in_y, int in_z);
};

