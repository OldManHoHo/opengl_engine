#ifndef TMC_CHUNK_DATABASE_H_
#define TMC_CHUNK_DATABASE_H_

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "tmc/coord_types.h"

namespace tmc
{

class ChunkDatabase
{
    std::string db_path;
 public:
    ChunkDatabase();
    void load_chunk(int chunk_x,
            int chunk_y,
            std::map <chunk_coord, std::map<block_coord, block_def>>& world_mods);
    void save_chunk(int chunk_x,
            int chunk_y,
            std::map <chunk_coord, std::map<block_coord, block_def>>& world_mods);
};

}  // namespace tmc

#endif  // TMC_CHUNK_DATABASE_H_
