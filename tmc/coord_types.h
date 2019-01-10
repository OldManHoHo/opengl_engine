#ifndef TMC_COORDTYPES_H_
#define TMC_COORDTYPES_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

#endif