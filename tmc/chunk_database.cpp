#include "tmc/chunk_database.h"

namespace tmc
{

ChunkDatabase::ChunkDatabase()
{
    db_path = "./server_data";
}

void ChunkDatabase::load_chunk(int chunk_x,
        int chunk_y,
        std::unordered_map <chunk_coord, std::unordered_map<block_coord, block_def>>& world_mods)
{
    chunk_coord chunk_to_load(chunk_x, chunk_y);
    std::ifstream chunk_file;
    std::string filename =
        std::to_string(chunk_x) + "x" + std::to_string(chunk_y) + ".dat";
    chunk_file.open(db_path + "/" + filename, std::ios::in | std::ios::binary);
    if (chunk_file.good())
    {
        uint32_t block_count;
        chunk_file.read(reinterpret_cast<char*>(&block_count), sizeof(uint32_t));
        for (int i = 0; i < block_count; ++i)
        {
            
            e_block_type block_type;
            uint16_t x;
            chunk_file.read(reinterpret_cast<char*>(&x), sizeof(uint16_t));
            uint16_t y;
            chunk_file.read(reinterpret_cast<char*>(&y), sizeof(uint16_t));
            uint16_t z;
            chunk_file.read(reinterpret_cast<char*>(&z), sizeof(uint16_t));
            uint8_t block_type_byte;
            chunk_file.read(reinterpret_cast<char*>(&block_type_byte),
                            sizeof(uint8_t));
            
            block_coord block_to_load(x, y, z);
            block_def block_def_to_load(x, y, z, (e_block_type)block_type_byte);
            
            if (world_mods.find(chunk_to_load) == world_mods.end())
            {
                world_mods[chunk_to_load] = std::unordered_map<block_coord, block_def>();
            }
            //world_mods[chunk_to_load][block_to_load] = block_def_to_load;
        }
        // chunk_file << "Writing this to a file.\n";
        chunk_file.close();
    }
}

void ChunkDatabase::save_chunk(int chunk_x,
        int chunk_y,
        std::unordered_map <chunk_coord, std::unordered_map<block_coord, block_def>>& world_mods)
{
    std::ofstream chunk_file;
    std::string filename =
        std::to_string(chunk_x) + "x" + std::to_string(chunk_y) + ".dat";
    chunk_file.open(db_path + "/" + filename, std::ios::out | std::ios::binary);
    if (chunk_file.good())
    {
        chunk_coord chunk_to_write(chunk_x, chunk_y);
        if (world_mods.find(chunk_to_write) != world_mods.end())
        {
            uint32_t block_count = world_mods[chunk_to_write].size();
            chunk_file.write(reinterpret_cast<char*>(&block_count),
                             sizeof(uint32_t));
            for (auto block : world_mods[chunk_to_write])
            {
                uint16_t x = block.second.loc.x;
                uint16_t y = block.second.loc.y;
                uint16_t z = block.second.loc.z;
                uint8_t block_type_byte = (uint8_t)block.second.type;
                chunk_file.write(reinterpret_cast<char*>(&x), sizeof(uint16_t));
                chunk_file.write(reinterpret_cast<char*>(&y), sizeof(uint16_t));
                chunk_file.write(reinterpret_cast<char*>(&z), sizeof(uint16_t));
                chunk_file.write(reinterpret_cast<char*>(&block_type_byte),
                                 sizeof(uint8_t));
            }
        }
    }
}

}  // namespace tmc
