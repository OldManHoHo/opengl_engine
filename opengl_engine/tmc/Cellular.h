#ifndef TMC_CELLULAR_H_
#define TMC_CELLULAR_H_

#pragma once
#include "FastNoiseSIMD/FastNoiseSIMD.h"
#include "tmc/Generator.h"
class Cellular :
	public Generator
{
	FastNoiseSIMD* myNoise;
	float* noiseSet;
	float scale;

public:
	Cellular(int in_seed, float in_scale = 0);
	~Cellular();

	float get_point(int in_x, int in_y, int in_z);
	float get_point_2d(int in_x, int in_y);
	float * get_points(int in_x, int in_y, int in_z, int division);
	float * get_points_2d(int in_x, int in_y, int division);
};

#endif