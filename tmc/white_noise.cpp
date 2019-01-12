#include "tmc/white_noise.h"


namespace tmc
{

WhiteNoise::WhiteNoise(int in_seed, float in_scale)
{
    myNoise = FastNoiseSIMD::NewFastNoiseSIMD(in_seed);
    noiseSet = nullptr;
    scale = in_scale;
}


WhiteNoise::~WhiteNoise()
{
    FastNoiseSIMD::FreeNoiseSet(noiseSet);
}

float WhiteNoise::get_point(int in_x, int in_y, int in_z)
{
    return 0;
}

float WhiteNoise::get_point_2d(int in_x, int in_y)
{
    return 0;
}

float * WhiteNoise::get_points(int in_x, int in_y, int in_z, int division)
{
    // Get a set of 16 x 16 x 16 WhiteNoise Fractal noise
    if (noiseSet != nullptr)
    {
        FastNoiseSIMD::FreeNoiseSet(noiseSet);
    }
    // myNoise->SetAxisScales(1.0, 1.0, 16.0 / 256);
    noiseSet = myNoise->GetWhiteNoiseSet(in_x,
                                         in_y,
                                         in_z,
                                         division,
                                         division,
                                         256,
                                         scale);
    return noiseSet;
}


float * WhiteNoise::get_points_2d(int in_x, int in_y, int division)
{
    // Get a set of 16 x 16 x 16 WhiteNoise Fractal noise
    if (noiseSet != nullptr)
    {
        FastNoiseSIMD::FreeNoiseSet(noiseSet);
    }
    noiseSet = myNoise->GetWhiteNoiseSet(in_x,
                                         in_y,
                                         0,
                                         division,
                                         division,
                                         1,
                                         scale);
    return noiseSet;
}

}  // namespace tmc
