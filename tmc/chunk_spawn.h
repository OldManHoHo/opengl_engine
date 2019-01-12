#pragma once
#ifndef TMC_CHUNK_SPAWN_H_
#define TMC_CHUNK_SPAWN_H_

#include <map>

#include <vector>
#include <deque>
#include <mutex>
#include <utility>

#include "tgl/tgl_gl.h"
#include "tgl/actor.h"
#include "tgl/chunk.h"
#include "tgl/mesh.h"
#include "tmc/block_generator.h"
// #include "TMCDroppedItem.h"

namespace tmc
{

struct face_map_pair
{
    int normal;
    int x;
    int y;
};

typedef double HitProperties;

struct BlockHit
{
    glm::vec3 loc;
    e_block_type type;
    HitProperties props;
};

template <class keyClass, class elementClass>
class chunk_searcher
{
 public:
    std::map <keyClass, std::vector<elementClass>> listing;
    void add_item(elementClass in_item, keyClass key);
    void remove_item(elementClass in_item, keyClass key);
    keyClass find_item(elementClass in_item);
};

class ChunkSpawn : public tgl::Actor
{
    std::map <chunk_coord, tmc::Chunk*> chunks;

    tgl::MeshVertices * block_mesh_vertices;
    tgl::Texture * block_texture;
    tgl::Material * block_material;

    BlockGenerator * block_generator;
    std::vector <block_def> new_block_changes;

    int block_type_count;

    std::vector <tgl::Mesh*> meshes;
    std::vector <chunk_coord> chunks_to_load;

    std::deque <BlockHit> posted_hits;
    static const unsigned int hits_to_break = 1;
    std::deque <block_def> posted_placements;
    // td::unordered_map <chunk_coord, std::vector<tgl::Actor*>> dropped_items;
    chunk_searcher<chunk_coord, tgl::Actor*> dropped_items;

    std::map <chunk_coord, std::map<block_coord, unsigned char>> light_calcs;
    std::map <chunk_coord, std::map<block_coord, glm::vec3>> light_calcs_vec;
    std::mutex light_calcs_mutex;
    glm::vec3 sun_dir;
    std::mutex sun_dir_mutex;

    bool test_chunk;
    static e_block_type pointed_at;

 public:
    ChunkSpawn();
    glm::vec3 get_block_pointed_at(glm::vec3 origin,
                                   glm::vec3 pointing_vector,
                                   double max_distance,
                                   e_block_type& out_block_type,
                                   glm::vec3& out_prev_block,
                                   glm::vec3& intersect_point);
    void tick(double time_delta);
    void spawn_chunk(int chunk_x, int chunk_y);
    void despawn_chunk(int chunk_x, int chunk_y);
    std::vector <GLfloat> create_uv_map(std::vector <face_map_pair> pairs);
    bool between_angles(float x, float y, float in_angle_1, float in_angle_2);
    std::vector <chunk_coord> get_chunks(int x0,
                                         int y0,
                                         int radius,
                                         float view_angle_1,
                                         float view_angle_2);
    e_block_type get_point(int x, int y, int z);
    void set_point(int x, int y, int z, e_block_type b_type);
    e_block_type * get_points(int x, int y, int division);
    void get_chunk_of_point(glm::vec3 in_point,
                            int& out_chunk_x,
                            int& out_chunk_y);
    void post_hit(BlockHit in_hit);
    void post_placement(block_def in_block);
    std::vector <tgl::Actor*> collect_nearby_dropped_items(glm::vec3 pos,
                                                           double radius);
    void client_request_chunk(int chunk_x, int chunk_y);
    void server_send_chunk_mods(int chunk_x, int chunk_y);
    bool chunk_in_fov(int chunk_x,
                      int chunk_y,
                      glm::vec3 player,
                      glm::vec3 player_forward);
#ifdef _TGL_CLIENT
    std::vector <GLshort> get_block_light_value(int in_x,
                                                                 int in_y,
                                                                 int in_z);
#endif
    void recalculate_light();
    void update_lights();
    void set_sun_dir(glm::vec3 in_dir);
    std::vector <block_def>& get_block_changes();
    void clear_block_changes();
};

}  // namespace tmc

#endif  // TMC_CHUNK_SPAWN_H_
