#pragma once
#ifndef TMC_WHITE_NOISE_H_
#define TMC_WHITE_NOISE_H_

#include "FastNoiseSIMD/FastNoiseSIMD.h"
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
    explicit WhiteNoise(int in_seed, float in_scale = 0);
    ~WhiteNoise();

    float get_point(int in_x, int in_y, int in_z);
    float get_point_2d(int in_x, int in_y);
    float * get_points(int in_x, int in_y, int in_z, int division);
    float * get_points_2d(int in_x, int in_y, int division);
};

}  // namespace tmc

#endif  // TMC_WHITE_NOISE_H_
