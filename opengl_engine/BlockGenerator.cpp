#include "BlockGenerator.h"
#include "math.h"
#include <chrono>
#include <algorithm>



BlockGenerator::BlockGenerator(bool tester):test_gen(tester)
{
	auto timet = std::chrono::system_clock::now();
	seed = 7;// std::chrono::duration_cast<std::chrono::seconds>(timet.time_since_epoch()).count() % 1000;
	height = new Simplex(10 + seed, 1);
	height2 = new Simplex(11 + seed, 4);
	height3 = new Simplex(13 + seed, 0.1);
	height4 = new Simplex(20 + seed, 0.01);
	height5 = new Simplex(21 + seed, 0.05);
	mountains = new Simplex(22 + seed, 0.4);
	//mountains->set_scales(0.9999, 1.0, 1.0);
	mountains2 = new Simplex(23 + seed, 0.2);
	//mountains2->set_scales(0.99999, 1.0, 1.0);
	trees = new WhiteNoise(12 + seed, 1);
	caves = new Simplex(15 + seed, 2);
	caves2 = new Simplex(16 + seed, 0.3);
	blocks = nullptr;
}

 
BlockGenerator::~BlockGenerator()
{
}


e_block_type BlockGenerator::get_point(int in_x, int in_y, int in_z)
{
	std::lock_guard<std::recursive_mutex> Lock(access_mutex);
	if (test_gen)
	{
		e_block_type type = static_cast<e_block_type>((abs(int(floor(in_x / 16.0) + floor(in_z / 16.0)))) % 6);
		if (in_z == 180)
		{
			return type;
		}
		return bt_air;
	}

	block_def d1;
	d1.loc = block_coord(1, 2, 3);
	d1.type = bt_tree;

	e_block_type new_type = check_for_mod(in_x, in_y, in_z);
	if (new_type != bt_invalid)
	{
		return new_type;
	}

	float * noises = height->get_points_2d(in_x, in_y, 1);
	float * noises2 = height2->get_points_2d(in_x, in_y, 1);
	float * noises3 = height3->get_points_2d(in_x, in_y, 1);
	float * noises4 = height4->get_points_2d(in_x, in_y, 1);
	float * noises5 = height5->get_points_2d(in_x, in_y, 1);
	float * mount_noise = mountains->get_points_2d(in_x, in_y, 1);
	float * mount_noise2 = mountains2->get_points_2d(in_x, in_y, 1);
	float * trees_noise = trees->get_points(in_x, in_y, in_z, 1);
	float * caves_noise = caves->get_points(in_x, in_y, in_z, 1);
	float * caves_noise2 = caves2->get_points(in_x, in_y, in_z, 1);

	e_block_type block = bt_air;

	float mountain_draw = mount_noise[0] * abs(mount_noise2[0]);
	int height_draw = abs(noises5[0])*(
		(noises[0] * 3.0 / 4 + noises2[0] / 4) * 10 +
		abs(noises3[0]) * 50 +
		noises4[0] * 60 +
		mountain_draw * 60) + 175;
	//fprintf(outfile, "%i, %i, %i, %f\n", j, k, i, caves_noise[j*division * 256 + k * 256 + i])
	//return int(height_draw);
	/*
	if (int(in_z) == height_draw)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	*/
	
	if (block > 0 && block < 8)
	{

	}
	else if ((in_z >(height_draw) ||
		(abs(caves_noise[0]) < 0.08))) //2+abs(caves_noise2[counter])/2)//caves_noise[counter]/2+caves_noise2[counter]/2 > 0.4)//(i > (noises[j*division + k] * 3.0 / 4 + noises2[j*division + k] / 4) * 10 + 175)//(i > (noises[j*division + k]*3.0/4 + noises2[j*division + k]/4) * 10 + 175) || 
	{
		//blocks[((j*division*division) + k*division) + i] = 0;
		//blocks[((j * 18 * 256) + k * 256) + i] = 0;
		if (in_z < 171)
		{
			block = bt_water;
		}
		else
		{
			block = bt_air;
		}

	}
	else
	{
		//blocks[counter] = 2;
		//blocks[((j*division*division) + k*256) + i] = 1;
		if (int(height_draw) == in_z)
		{
			if (in_z <= 174)
			{
				block = bt_sand;
			}
			else if (mountain_draw > 0.3)
			{
				block = bt_stone;
			}
			else
			{
				block = bt_dirt_with_grass;
			}

		}
		else if (in_z < height_draw - 5 || mountain_draw > 0.3)
		{
			block = bt_stone;
		}
		else
		{
			if (in_z <= 174)
			{
				block = bt_sand;
			}
			else
			{
				block = bt_dirt;
			}

		}

	}
	return block;
}


e_block_type BlockGenerator::get_point_2d(int in_x, int in_y)
{
	return bt_air;
}

e_block_type * BlockGenerator::get_points(int in_x, int in_y, int in_z, int division)
{
	std::lock_guard<std::recursive_mutex> Lock(access_mutex);
	if (blocks != nullptr)
	{
		delete[] blocks;
	}

	blocks = new e_block_type[division * division * 256]{bt_air};
	float * noises = height->get_points_2d(in_x, in_y, division);
	float * noises2 = height2->get_points_2d(in_x, in_y, division);
	float * noises3 = height3->get_points_2d(in_x, in_y, division);
	float * noises4 = height4->get_points_2d(in_x, in_y, division);
	float * noises5 = height5->get_points_2d(in_x, in_y, division);
	float * mount_noise = mountains->get_points_2d(in_x, in_y, division);
	float * mount_noise2 = mountains2->get_points_2d(in_x, in_y, division);
	float * trees_noise = trees->get_points(in_x, in_y, in_z, division);
	float * caves_noise = caves->get_points(in_x, in_y, in_z, division);
	float * caves_noise2 = caves2->get_points(in_x, in_y, in_z, division);
	size_x = division;
	size_y = division;
	counter = 0;
	//for (int i = 0; i < 256; i++)
	//{
	//	for (int j = 0; j < division; j++)
	//	{
	//		for (int k = 0; k < division; k++)
	//		{
	//			if (caves_noise[j*division*256 + k*256 + i] > 0)//(i > (noises[j*division + k] * 3.0 / 4 + noises2[j*division + k] / 4) * 10 + 175)//(i > (noises[j*division + k]*3.0/4 + noises2[j*division + k]/4) * 10 + 175) || 
	//			{
	//				//blocks[((j*division*division) + k*division) + i] = 0;
	//				blocks[((i * 18 * 18) + j * 18) + k] = 0;
	//			}
	//			else
	//			{
	//				//blocks[((j*division*division) + k*256) + i] = 1;
	//				blocks[((i * 18 * 18) + j * 18) + k] = 1;
	//			}
	//			counter++;
	//		}
	//	}
	//}
	//FILE * outfile = fopen("C:\out.csv", "w");
	for (int j = 0; j < division; j++)
	//for (int j = division-1; j >= 0; --j)
	{
		for (int k = 0; k < division; k++)
		//for (int k = division-1; k >= 0; --k)
		{
			for (int i = 0; i < 256; i++)
			{
				e_block_type mod = check_for_mod(in_x + j, in_y + k, in_z + i);
				if (mod == bt_invalid)
				{
					float mountain_draw = mount_noise[j*division + k] * abs(mount_noise2[j*division + k]);
					int height_draw = abs(noises5[j*division + k])*(
						(noises[j*division + k] * 3.0 / 4 + noises2[j*division + k] / 4) * 10 +
						abs(noises3[j*division + k]) * 50 +
						noises4[j*division + k] * 60 +
						mountain_draw * 60) + 175;
					//fprintf(outfile, "%i, %i, %i, %f\n", j, k, i, caves_noise[j*division * 256 + k * 256 + i])
					if (blocks[counter] > 0 && blocks[counter] < 8)
					{

					}
					else if ((i > (height_draw) ||
						(abs(caves_noise[counter]) < 0.08))) //2+abs(caves_noise2[counter])/2)//caves_noise[counter]/2+caves_noise2[counter]/2 > 0.4)//(i > (noises[j*division + k] * 3.0 / 4 + noises2[j*division + k] / 4) * 10 + 175)//(i > (noises[j*division + k]*3.0/4 + noises2[j*division + k]/4) * 10 + 175) || 
					{
						//blocks[((j*division*division) + k*division) + i] = 0;
						//blocks[((j * 18 * 256) + k * 256) + i] = 0;
						if (i < 171)
						{
							blocks[counter] = bt_water;
						}
						else
						{
							blocks[counter] = bt_air;
						}

					}
					else
					{
						//blocks[counter] = 2;
						//blocks[((j*division*division) + k*256) + i] = 1;
						if (int(height_draw) == i)
						{
							if (i <= 174)
							{
								blocks[counter] = bt_sand;
							}
							else if (mountain_draw > 0.3)
							{
								blocks[counter] = bt_stone;
							}
							else
							{
								blocks[counter] = bt_dirt_with_grass;
							}

							if (abs(trees_noise[counter]) + abs(noises[j*division + k])*0.1 < 0.04)
							{
								int chunk_x = floor((in_x) / 16.0);
								int chunk_y = floor((in_y) / 16.0);
								get_tree(trees_noise, blocks, j, k, i, chunk_x, chunk_y);
							}
						}
						else if (i < height_draw - 5 || mountain_draw > 0.3)
						{
							blocks[counter] = bt_stone;
						}
						else
						{
							if (i <= 174)
							{
								blocks[counter] = bt_sand;
							}
							else
							{
								blocks[counter] = bt_dirt;
							}

						}

					}
				}
				else
				{
					blocks[counter] = mod;
				}
				//int block_type_test = get_point(in_x + k, in_y + j, i);
				//if (blocks[counter] != block_type_test)
				//{
				//	printf("FART2\n");
				//}
				counter++;
			}
		}
	}
	/*
	if (block_file.has_chunk(in_x, in_y))
	{
		auto chunk = block_file.get_chunk(in_x, in_y);
		for (auto it = chunk->begin(); it != chunk->end(); ++it)
		{
			blocks[it->x*division * 256 + it->y * 256 + it->z] = it->value;
		}
	}
	*/
	return blocks;
}

e_block_type * BlockGenerator::get_points_2d(int in_x, int in_y, int division)
{
	return nullptr;
}

void BlockGenerator::set_point(e_block_type in_block_type, int in_x, int in_y, int in_z)
{
	std::lock_guard<std::recursive_mutex> Lock(access_mutex);
	int chunk_x = floor(in_x / 16.0);
	int chunk_y = floor(in_y / 16.0);
	chunk_coord chunk_loc(chunk_x, chunk_y);
	if (world_mods.find(chunk_loc) != world_mods.end())
	{
		block_def def;
		def.loc = block_coord(in_x - chunk_x * 16, in_y - chunk_y * 16, in_z);
		def.type = in_block_type;
		//auto ind = std::find(world_mods[chunk_loc].begin(), world_mods[chunk_loc].end(), def);

		if (world_mods[chunk_loc].find(def.loc) != world_mods[chunk_loc].end())
		{
			//(*ind).type = in_block_type;
			world_mods[chunk_loc][def.loc].type = in_block_type;
		}
		else
		{
			//world_mods[chunk_loc].push_back(def);
			world_mods[chunk_loc][def.loc] = def;
		}
	}
	else
	{
		block_def def;
		def.loc = block_coord(in_x - chunk_x * 16, in_y - chunk_y * 16, in_z);
		def.type = in_block_type;
		world_mods[chunk_loc] = std::map<block_coord,block_def>();
		world_mods[chunk_loc][def.loc] = def;
	}
}

e_block_type BlockGenerator::check_for_mod(int in_x, int in_y, int in_z)
{
	std::lock_guard<std::recursive_mutex> Lock(access_mutex);
	int chunk_x = floor(in_x / 16.0);
	int chunk_y = floor(in_y / 16.0);
	chunk_coord chunk_loc(chunk_x, chunk_y);
	if (world_mods.find(chunk_loc) != world_mods.end())
	{
		block_def def;
		def.loc = block_coord(in_x - chunk_x * 16, in_y - chunk_y * 16, in_z);
		if (world_mods[chunk_loc].size())
		{
			//auto ind = std::find(world_mods[chunk_loc].begin(), world_mods[chunk_loc].end(), def);
			if (world_mods[chunk_loc].find(def.loc) != world_mods[chunk_loc].end())
			{
				//return (*ind).type;
				return world_mods[chunk_loc][def.loc].type;
			}
		}
	}
	return bt_invalid;
}

e_block_type BlockGenerator::index(int in_x, int in_y, int in_z)
{
	std::lock_guard<std::recursive_mutex> Lock(access_mutex);
	e_block_type retval = blocks[(size_x*256*in_x) + (256*in_y) + in_z];
	return retval;
}

bool BlockGenerator::is_visible(int in_x, int in_y, int in_z)
{
	std::lock_guard<std::recursive_mutex> Lock(access_mutex);
	if (index(in_x, in_y, in_z + 1) != bt_air && index(in_x, in_y, in_z + 1) != bt_water && index(in_x, in_y, in_z + 1) != bt_leaves)// && index(in_x, in_y, in_z + 1) != 5 && index(in_x, in_y, in_z + 1) != 6 )
	{
		if (index(in_x, in_y, in_z - 1) != bt_air && index(in_x, in_y, in_z - 1) != bt_water && index(in_x, in_y, in_z - 1) != bt_leaves)// && index(in_x, in_y, in_z - 1) != 5 && index(in_x, in_y, in_z - 1) != 6 )
		{
			if (index(in_x, in_y + 1, in_z) != bt_air && index(in_x, in_y + 1, in_z) != bt_water && index(in_x, in_y + 1, in_z) != bt_leaves)// && index(in_x, in_y + 1, in_z) != 5 && index(in_x, in_y + 1, in_z) != 6 )
			{
				if (index(in_x, in_y - 1, in_z) != bt_air && index(in_x, in_y - 1, in_z) != bt_water && index(in_x, in_y - 1, in_z) != bt_leaves)// && index(in_x, in_y - 1, in_z) != 5 && index(in_x, in_y - 1, in_z) != 6 )
				{
					if (index(in_x + 1, in_y, in_z) != bt_air && index(in_x + 1, in_y, in_z) != bt_water && index(in_x + 1, in_y, in_z) != bt_leaves)// && index(in_x + 1, in_y, in_z) != 5 && index(in_x + 1, in_y, in_z) != 6 )
					{
						if (index(in_x - 1, in_y, in_z) != bt_air && index(in_x - 1, in_y, in_z) != bt_water && index(in_x - 1, in_y, in_z) != bt_leaves)// && index(in_x - 1, in_y, in_z) != 5 && index(in_x - 1, in_y, in_z) != 6)
						{
							return 0;
						}
					}
				}
			}
		}
	}
	return 1;
	bool retval = !(index(in_x, in_y, in_z + 1)*index(in_x, in_y, in_z - 1)*index(in_x, in_y + 1, in_z)*index(in_x, in_y - 1, in_z)
		*index(in_x + 1, in_y, in_z)*index(in_x - 1, in_y, in_z));
	return retval;
}

void BlockGenerator::get_tree(float * in_noise, e_block_type * in_blocks, int in_x, int in_y, int in_z, int chunk_x, int chunk_y)
{
	std::lock_guard<std::recursive_mutex> Lock(access_mutex);
	int count = 1;
	float prob = 0.99;
	float branch_prob = 0.9;
	//in_blocks[in_x * 18 * 256 + in_y * 256 + in_z + 2] = 4;
	//in_blocks[in_x * 18 * 256 + in_y * 256 + in_z + 3] = 4;
	while (1)
	{
		if (in_z + count > 250)
		{
			break;
		}
		in_blocks[in_x * size_x * 256 + in_y * 256 + in_z + count] = bt_tree;
		set_point(bt_tree, chunk_x * 16 + in_x, chunk_y * 16 + in_y, in_z + count);
		if (count > 2)
		{
			if (in_y + 1 <= 15)
			{
				if (abs(in_noise[in_x * size_x * 256 + (in_y + 1) * 256 + in_z + count]) > branch_prob)
				{
					in_blocks[in_x * size_x * 256 + (in_y + 1) * 256 + in_z + count] = bt_leaves;
					set_point(bt_leaves, chunk_x*16 + in_x, chunk_y * 16 + in_y + 1, in_z + count);
				}
			}
			if (in_y - 1 >= 0)
			{
				if (abs(in_noise[in_x * size_x * 256 + (in_y - 1) * 256 + in_z + count]) > branch_prob)
				{
					in_blocks[in_x * size_x * 256 + (in_y - 1) * 256 + in_z + count] = bt_leaves;
					set_point(bt_leaves, chunk_x * 16 + in_x, chunk_y * 16 + in_y - 1, in_z + count);
				}
			}
			if (in_x + 1 <= 15)
			{
				if (abs(in_noise[(in_x + 1) * size_x * 256 + in_y * 256 + in_z + count]) > branch_prob)
				{
					in_blocks[(in_x + 1) * size_x * 256 + in_y * 256 + in_z + count] = bt_leaves;
					set_point(bt_leaves, chunk_x * 16 + in_x + 1, chunk_y * 16 + in_y, in_z + count);
				}
			}
			if (in_x - 1 >= 0)
			{
				if (abs(in_noise[(in_x - 1) * size_x * 256 + in_y * 256 + in_z + count]) > branch_prob)
				{
					in_blocks[(in_x - 1) * size_x * 256 + in_y * 256 + in_z + count] = bt_leaves;
					set_point(bt_leaves, chunk_x * 16 + in_x - 1, chunk_y * 16 + in_y, in_z + count);
				}
			}
			if (in_noise[in_x * size_x * 256 + in_y * 256 + in_z + count] > prob)
			{
				break;
			}
		}
		prob *= 0.6;
		branch_prob *= 0.5;
		count += 1;
	}
}
