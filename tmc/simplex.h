#ifndef TMC_SIMPLEX_H_
#define TMC_SIMPLEX_H_

#pragma once
#include "tgl/FastNoiseSIMD/FastNoiseSIMD.h"
#include "tmc/generator.h"

namespace tmc
{

class Simplex :
	public Generator
{
public:
	FastNoiseSIMD* myNoise;
	float* noiseSet;
	float scale;

public:
	Simplex(int in_seed, float in_scale = 0);
	~Simplex();

	float get_point(int in_x, int in_y, int in_z);
	float get_point_2d(int in_x, int in_y);
	float * get_points(int in_x, int in_y, int in_z, int division);
	float * get_points_2d(int in_x, int in_y, int division);
	void set_scales(int in_x, int in_y, int in_z);
};

#ifdef _UNIT_TEST
void Simplex_TEST();
#endif

} // namespace tmc

#endif