#ifndef TMC_CHUNKDATABASE_H_
#define TMC_CHUNKDATABASE_H_

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "TMCCoordTypes.h"

class TMCChunkDatabase
{
    std::string db_path;
    
public:
    TMCChunkDatabase();
    void load_chunk(int chunk_x, int chunk_y, std::map <chunk_coord, std::map<block_coord,block_def>>& world_mods);
    void save_chunk(int chunk_x, int chunk_y, std::map <chunk_coord, std::map<block_coord,block_def>>& world_mods);
};

#endif