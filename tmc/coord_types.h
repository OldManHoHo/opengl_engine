#ifndef TMC_COORD_TYPES_H_
#define TMC_COORD_TYPES_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum e_block_type
{
    bt_air,
    bt_dirt_with_grass,
    bt_dirt,
    bt_stone,
    bt_tree,
    bt_leaves,
    bt_water,
    bt_sand,
    bt_invalid
};

struct chunk_coord
{
    chunk_coord(int in_x=0, int in_y=0) { x = in_x; y = in_y; }
    int x;
    int y;
    const bool operator < (const chunk_coord &r) const {
        return (x < r.x) || (x == r.x && y < r.y);
    }
    const bool operator == (const chunk_coord &r) const {
        return x == r.x && y == r.y;
    }
    template <class Archive>
    void serialize( Archive & ar )
    {
        ar( x, y );
    }
};

struct block_coord
{
    block_coord() {}
    explicit block_coord(glm::vec3 in_vec)
    {
        x = in_vec.x;
        y = in_vec.y;
        z = in_vec.z;
    }

    block_coord(int in_x, int in_y, int in_z) {
        x = in_x; y = in_y; z = in_z;
    }

    bool operator==(const block_coord& in_coord) const
    {
        return (in_coord.x == x && in_coord.y == y && in_coord.z == z);
    }

    const bool operator < (const block_coord &r) const {
        return (x < r.x) ||
            (x == r.x && y < r.y) ||
            (x == r.x && y == r.y && z < r.z);
    }

    glm::vec3 get_vec() { return glm::vec3(x, y, z); }
    int x;
    int y;
    int z;
    
    template <class Archive>
    void serialize( Archive & ar )
    {
        ar( x, y, z );
    }
};

struct block_def
{
    block_coord loc;
    e_block_type type;
    block_def() {}
    block_def(int in_x, int in_y, int in_z, e_block_type in_type) :
        loc(in_x, in_y, in_z),
        type(in_type)
    {}
    bool operator== (const block_def& in_def)
    {
        return loc == in_def.loc;
    }
    
    template <class Archive>
    void serialize( Archive & ar )
    {
        ar( loc, type );
    }
};

namespace std
{
    template <>
    struct hash<chunk_coord>
    {
        size_t operator()(const chunk_coord& k) const
        {
            // Compute individual hash values for two data members and combine them using XOR and bit shifting
            return ((k.x*0x1f1f1f1f)^(k.y*0xf1f1f1f1));
        }
    };

    template <>
    struct hash<block_coord>
    {
        size_t operator()(const block_coord& k) const
        {
            // Compute individual hash values for two data members and combine them using XOR and bit shifting
            return ((k.x * 0x1f1f1f1f) ^ (k.y * 0xf1f1f1f1) ^ (k.z * 0x2e2e2e2e));
        }
    };
}  // namespace std

#endif  // TMC_COORD_TYPES_H_
