#include "tgl/physics_engine.h"

#include <math.h>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <iostream>

#include "tgl/bounds.h"

namespace tgl
{

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

double clamp(double value, double min, double max)
{
    if (value < min)
    {
        return min;
    }
    if (value > max)
    {
        return max;
    }
    return value;
}

PhysicsEngine::PhysicsEngine()
{
    // fopen(&out_file, "test.text", "a");
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::tick(double time_delta,
                         std::vector <tgl::Actor*> const & actors,
                         tmc::ChunkSpawn * chunks_spawner,
                         bool gravity_enabled)
{
    float gravity = 9.81;
    if (!gravity_enabled)
    {
        gravity = 0;
    }
    for (auto it = actors.begin(); it != actors.end(); ++it)
    {
        if ((*it)->get_bounds() != nullptr)
        {
            if ((*it)->mass > 0)
            {
                // std::ofstream out_file;
                // out_file.open("test.txt", std::ios::app);

                std::shared_ptr<tgl::BlockBounds> bounds =
                    std::dynamic_pointer_cast<tgl::BlockBounds>
                        ((*it)->get_bounds());
                glm::vec3 feet = (*it)->get_pos() -
                                 glm::vec3(0, bounds->height, 0);

                feet = glm::vec3(round(feet.x), round(feet.y), round(feet.z));
                e_block_type in_type = chunks_spawner->get_point(round(feet.x),
                    round(feet.y), round(feet.z));

                (*it)->set_on_ground(false);
                (*it)->vel += static_cast<float>(time_delta)*(*it)->accel +
                              static_cast<float>(time_delta*gravity)*
                                glm::vec3(0, -1.0, 0);

                double speed_mult = 1.0;
                if (in_type == bt_water)
                {
                    speed_mult = 0.25;
                    (*it)->set_on_ground(true);
                }

                std::vector <glm::vec3> collision_blocks =
                    get_world_blocks((*it), chunks_spawner);
                move(time_delta, (*it), collision_blocks, speed_mult);
                /*
                
                for (auto block_it = collision_blocks.begin();
                     block_it != collision_blocks.end();
                     ++block_it)
                {
                    //collide_cylinder_and_block((*it), (*block_it));
                    collide_aligned_block_and_block2((*it), (*block_it));
                }
                (*it)->prev_pos = (*it)->pos;
                (*it)->pos += float(time_delta)*(*it)->vel;
                (*it)->vel += float(time_delta)*(*it)->accel + float(time_delta*9.81)*glm::vec3(0, -1.0, 0);
                //fprintf(out_file,"velocity: %f,%f,%f\n", (*it)->vel.y, (*it)->pos.y, time_delta);
                //out_file << "velocity:" << (*it)->vel.y << ", " << time_delta << "\n";
                //out_file.close();
                //fclose(out_file);
                */
            }
        }
    }
}

std::vector <glm::vec3> PhysicsEngine::get_world_blocks(
    tgl::Actor * in_actor,
    tmc::ChunkSpawn * chunks_spawner)
{
    glm::vec3 position = in_actor->get_pos();

    // tgl::BlockBounds * actor_bounds =
    //      (tgl::BlockBounds*)(in_actor->get_bounds());
    std::shared_ptr<tgl::BlockBounds> actor_bounds =
        std::dynamic_pointer_cast<tgl::BlockBounds>(in_actor->get_bounds());
    std::vector <glm::vec3> out_points;

    // TODO(Teddy Walsh): Get rid of most of this shit
    int x[3];
    int y[5];
    int z[3];

    x[0] = static_cast<int>(round(position.x));
    x[1] = static_cast<int>(round(position.x)) - 1;
    x[2] = static_cast<int>(round(position.x)) + 1;

    y[0] = static_cast<int>(round(position.y));
    y[1] = static_cast<int>(round(position.y)) - 1;
    y[2] = static_cast<int>(round(position.y)) + 1;

    z[0] = static_cast<int>(round(position.z));
    z[1] = static_cast<int>(round(position.z)) - 1;
    z[2] = static_cast<int>(round(position.z)) + 1;


    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                e_block_type block_type =
                    chunks_spawner->get_point(x[i], y[j], z[k]);
                if (block_type != bt_air && block_type != bt_water)
                {
                    out_points.push_back(glm::vec3(x[i], y[j], z[k]));
                    // out_points.push_back(glm::vec3(x[i], 175, z[k]));
                }
            }
        }
    }
    return out_points;
}

void PhysicsEngine::move(double time_delta,
                         tgl::Actor * in_actor,
                         std::vector <glm::vec3> in_blocks,
                         double in_speed_mult)
{
    in_actor->pos.x += in_actor->vel.x*time_delta*in_speed_mult;
    // tgl::BlockBounds * actor_bounds =
    //      (tgl::BlockBounds*)(in_actor->get_bounds());
    std::shared_ptr<tgl::BlockBounds> actor_bounds =
        std::dynamic_pointer_cast<tgl::BlockBounds>(in_actor->get_bounds());
    double block_height = 1.0;
    double block_width = 1.0;
    double block_depth = 1.0;
    for (auto in_block : in_blocks)
    {
        double y_pen = -std::abs(in_actor->pos.y - in_block.y) +
                       (actor_bounds->height / 2.0 + block_height / 2.0);
        double x_pen = -std::abs(in_actor->pos.x - in_block.x) +
                       (actor_bounds->width / 2.0 + block_width / 2.0);
        double z_pen = -std::abs(in_actor->pos.z - in_block.z) +
                       (actor_bounds->depth / 2.0 + block_depth / 2.0);
        if (y_pen > 0 && x_pen > 0 && z_pen > 0)
        {
            in_actor->pos.x -= x_pen*sign(in_actor->vel.x)*1.01;
            in_actor->vel.x = 0;
        }
    }

    in_actor->pos.z += in_actor->vel.z*time_delta*in_speed_mult;
    for (auto in_block : in_blocks)
    {
        double y_pen = -std::abs(in_actor->pos.y - in_block.y) +
                       (actor_bounds->height / 2.0 + block_height / 2.0);
        double x_pen = -std::abs(in_actor->pos.x - in_block.x) +
                       (actor_bounds->width / 2.0 + block_width / 2.0);
        double z_pen = -std::abs(in_actor->pos.z - in_block.z) +
                       (actor_bounds->depth / 2.0 + block_depth / 2.0);
        if (y_pen > 0 && x_pen > 0 && z_pen > 0)
        {
            in_actor->pos.z -= z_pen*sign(in_actor->vel.z)*1.01;
            in_actor->vel.z = 0;
        }
    }

    in_actor->pos.y += in_actor->vel.y*time_delta*in_speed_mult;
    for (auto in_block : in_blocks)
    {
        double y_pen = -std::abs(in_actor->pos.y - in_block.y) +
                       (actor_bounds->height / 2.0 + block_height / 2.0);
        double x_pen = -std::abs(in_actor->pos.x - in_block.x) +
                       (actor_bounds->width / 2.0 + block_width / 2.0);
        double z_pen = -std::abs(in_actor->pos.z - in_block.z) +
                       (actor_bounds->depth / 2.0 + block_depth / 2.0);
        if (y_pen > 0 && x_pen > 0 && z_pen > 0)
        {
            in_actor->pos.y -= y_pen*sign(in_actor->vel.y)*1.01;
            in_actor->vel.y = 0;
            in_actor->set_on_ground(true);
        }
    }
}

}  // namespace tgl
