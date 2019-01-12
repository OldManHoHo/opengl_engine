#include "tmc/simplex.h"

#include <vector>

namespace tmc
{

Simplex::Simplex(int in_seed, float in_scale)
{
    myNoise = FastNoiseSIMD::NewFastNoiseSIMD(in_seed);
    noiseSet = nullptr;
    scale = in_scale;
}


Simplex::~Simplex()
{
    FastNoiseSIMD::FreeNoiseSet(noiseSet);
}

float Simplex::get_point(int in_x, int in_y, int in_z)
{
    return 0;
}

float Simplex::get_point_2d(int in_x, int in_y)
{
    return 0;
}

float * Simplex::get_points(int in_x, int in_y, int in_z, int division)
{
    // Get a set of 16 x 16 x 16 Simplex Fractal noise
    if (noiseSet != nullptr)
    {
        FastNoiseSIMD::FreeNoiseSet(noiseSet);
    }
    // myNoise->SetAxisScales(1.0, 1.0, 16.0 / 256);
    if (division == 1)
    {
        noiseSet = myNoise->GetSimplexSet(in_x,
                                          in_y,
                                          in_z,
                                          division,
                                          division,
                                          1,
                                          scale);
    }
    else
    {
        noiseSet = myNoise->GetSimplexSet(in_x,
                                          in_y,
                                          in_z,
                                          division,
                                          division,
                                          256,
                                          scale);
    }
    return noiseSet;
}


float * Simplex::get_points_2d(int in_x, int in_y, int division)
{
    // Get a set of 16 x 16 x 16 Simplex Fractal noise
    if (noiseSet != nullptr)
    {
        FastNoiseSIMD::FreeNoiseSet(noiseSet);
    }
    noiseSet = myNoise->GetSimplexSet(in_x,
                                      in_y,
                                      0,
                                      division,
                                      division,
                                      1,
                                      scale);
    return noiseSet;
}

void Simplex::set_scales(int in_x, int in_y, int in_z)
{
    myNoise->SetAxisScales(in_x, in_y, in_z);
}

#ifdef _UNIT_TEST
#include <assert.h>
#include <iostream>
void Simplex_TEST()
{
    for (int s = 0; s < 100; s += 3)
    {
        Simplex simplex1(s, 0.0);
        Simplex simplex2(s, -1.0);
        Simplex simplex3(s, 1.0);
        Simplex simplex4(s, 0.5);
        Simplex simplex5(s, 0.0000001);
        Simplex simplex6(s, 2.0);
        Simplex simplex7(s, 3.0);
        Simplex simplex8(s, -1234567);
        Simplex simplex9(s, 1234567);

        std::vector <Simplex*> simplexes;
        simplexes.push_back(&simplex1);
        simplexes.push_back(&simplex2);
        simplexes.push_back(&simplex3);
        simplexes.push_back(&simplex4);
        simplexes.push_back(&simplex5);
        simplexes.push_back(&simplex6);
        simplexes.push_back(&simplex7);
        simplexes.push_back(&simplex8);
        simplexes.push_back(&simplex9);

        for (int i = 0; i < simplexes.size(); ++i)
        {
            for (int size_val = 4; size_val < 32; size_val += 3)
            {
                for (int offset = -size_val*2;
                     offset < size_val * 2;
                     offset += size_val)
                {
                    {
                        std::vector <float> points(size_val*size_val);
                        std::vector <float> points2(size_val*size_val);
                        float * out =
                            simplexes[i]->get_points_2d(offset, offset, size_val);
                        std::copy(out, out+size_val*size_val, points.begin());
                        out = simplexes[i]->get_points_2d(
                                                offset + static_cast<int>(size_val/2.0),
                                                offset + static_cast<int>(size_val/2.0),
                                                size_val);
                        std::copy(out, out+size_val*size_val, points2.begin());
                        for (int j = 0; j < static_cast<int>(size_val/2.0); ++j)
                        {
                            for (int k = 0; k < static_cast<int>(size_val/2.0); ++k)
                            {
                                if (points[size_val*(k+static_cast<int>(size_val/2.0)) + j + static_cast<int>(size_val/2.0)] != points2[size_val*(k) + j])
                                {
                                    std::cout <<
                                        "Simplex Unit Test FAILED on simplex: " <<
                                        i <<
                                        "\n";
                                    std::cout <<
                                        "\tValues: " <<
                                        points[size_val*(k+static_cast<int>(size_val/2.0)) + j + static_cast<int>(size_val/2.0)] <<
                                        ", " <<
                                        points2[size_val*(k) + j] <<
                                        "\n";
                                    assert(false);
                                }
                            }
                        }
                    }
                    {
                        std::vector <float> points(size_val*size_val*256);
                        std::vector <float> points2(size_val*size_val*256);
                        float * out = simplexes[i]->get_points(offset, offset, 0, size_val);
                        std::copy(out, out+size_val*size_val*256, points.begin());
                        out = simplexes[i]->get_points(offset + static_cast<int>(size_val/2.0), offset + static_cast<int>(size_val/2.0), 0, size_val);
                        std::copy(out, out+size_val*size_val*256, points2.begin());
                        for (int j = 0; j < static_cast<int>(size_val/2.0); ++j)
                        {
                            for (int k = 0; k < static_cast<int>(size_val/2.0); ++k)
                            {
                                for (int m = 150; m < 151; m+=16)
                                {
                                    if (points[size_val*256*(k+static_cast<int>(size_val/2.0)) + 256*(j + static_cast<int>(size_val/2.0)) + m] != points2[size_val*256*(k) + 256*(j) + m])
                                    {
                                        std::cout << "Simplex 3D Unit Test FAILED on simplex: " << i << "\n";
                                        std::cout << "\tValues: " << points[size_val*256*(k+static_cast<int>(size_val/2.0)) + 256*(j + static_cast<int>(size_val/2.0)) + m] << ", " << points2[size_val*256*(k) + 256*(j) + m] << "\n";
                                        assert(false);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << "Simplex Unit Test PASSED\n";
}

#endif

}  // namespace tmc
