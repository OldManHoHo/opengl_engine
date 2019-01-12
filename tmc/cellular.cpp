#include "tmc/cellular.h"

namespace tmc
{

Cellular::Cellular(int in_seed, float in_scale)
{
    myNoise = FastNoiseSIMD::NewFastNoiseSIMD(in_seed);
    noiseSet = nullptr;
    scale = in_scale;
}

Cellular::~Cellular()
{
    FastNoiseSIMD::FreeNoiseSet(noiseSet);
}

float Cellular::get_point(int in_x, int in_y, int in_z)
{
    return 0;
}

float Cellular::get_point_2d(int in_x, int in_y)
{
    return 0;
}

float * Cellular::get_points(int in_x, int in_y, int in_z, int division)
{
    // Get a set of 16 x 16 x 16 Cellular Fractal noise
    if (noiseSet != nullptr)
    {
        FastNoiseSIMD::FreeNoiseSet(noiseSet);
    }
    // myNoise->SetAxisScales(1.0, 1.0, 16.0 / 256);
    noiseSet = myNoise->GetCellularSet(in_x, in_y, in_z, division,
                                       division, 256, scale);
    return noiseSet;
}

float * Cellular::get_points_2d(int in_x, int in_y, int division)
{
    // Get a set of 16 x 16 x 16 Cellular Fractal noise
    if (noiseSet != nullptr)
    {
        FastNoiseSIMD::FreeNoiseSet(noiseSet);
    }
    noiseSet = myNoise->GetCellularSet(in_x, in_y, 0, division,
                                       division, 1, scale);
    return noiseSet;
}

}  // namespace tmc
