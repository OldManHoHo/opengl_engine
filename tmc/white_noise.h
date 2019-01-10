#pragma once
#ifndef TGL_WHITENOISE_H_
#define TGL_WHITENOISE_H_

#include "tgl/FastNoiseSIMD/FastNoiseSIMD.h"
#include "tmc/generator.h"

namespace tmc
{

class WhiteNoise :
	public Generator
{
	FastNoiseSIMD* myNoise;
	float* noiseSet;
	float scale;

public:
	WhiteNoise(int in_seed, float in_scale = 0);
	~WhiteNoise();
	
	float get_point(int in_x, int in_y, int in_z);
	float get_point_2d(int in_x, int in_y);
	float * get_points(int in_x, int in_y, int in_z, int division);
	float * get_points_2d(int in_x, int in_y, int division);
};

} // namespace tmc

#endif