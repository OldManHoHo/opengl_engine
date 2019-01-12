#ifndef TGL_INVENTORY_H_
#define TGL_INVENTORY_H_

#include <stdio.h>
#include <vector>

#include "tmc/block_generator.h"
#include "tmc/chunk_spawn.h"

namespace tgl
{

enum ItemId
{
    none,
    iid_dirt_with_grass_block,
    iid_dirt_block,
    iid_stone_block,
    iid_tree_block,
    iid_leaves_block,
    iid_water_block,
    iid_sand_block,
    pickaxe
};

e_block_type item_id_to_block_type(ItemId item_id);
// TODO(Teddy Walsh): this stuff should not be in TGL
ItemId block_type_to_item_id(e_block_type in_block_type);

class InventoryCoords
{
 public:
    InventoryCoords(unsigned int in_x, unsigned int in_y) :
        x(in_x), y(in_y)
    {   }
    unsigned int x;
    unsigned int y;
};

class InventoryItem
{
 public:
    unsigned int quantity;
    ItemId type;

    explicit InventoryItem(ItemId in_type = none, unsigned int in_quantity = 0);

    bool operator== (const InventoryItem& item_b);
    bool operator!= (const InventoryItem& item_b);

    tmc::HitProperties get_HitProperties();
};


// Inventory is intended to provide an abstraction of an inventory grid
// in which items in different quantities can be moved around, added, and
// deleted. The underlying data structure is a vector of InventoryItem
// pointers whose horizontal rows are x_size long and vertical columns
// are y_size long. It also provides the quick_use structure, intended
// to store easy access to 5 items in the Inventory's main vector.
class Inventory  //: public ::Component
{
    // object data
    unsigned int x_size;
    unsigned int y_size;
    std::vector <InventoryItem*> items;

 public:
    // class constants
    static const unsigned int default_quick_use_size = 5;
    static InventoryItem no_item;

    Inventory(int in_x_size, int in_y_size);

    // Item retrieval
    std::vector <InventoryItem*>& get_items();
    InventoryItem * get_item(unsigned int in_x, unsigned int in_y);
    InventoryItem * get_quick_use(unsigned int index);

    // Item Manipulation
    void set_item(unsigned int in_x,
                  unsigned int in_y,
                  ItemId in_type,
                  unsigned int in_quantity);
    bool move_item(unsigned int src_x,
                   unsigned int src_y,
                   unsigned int dest_x,
                   unsigned int dest_y);
    bool delete_item(unsigned int in_x, unsigned int in_y);
    bool change_quantity(ItemId in_type, int in_quantity);
    void print_inventory();

    // Management
    void repair_garbage();
};

}  // namespace tgl

#endif  // TGL_INVENTORY_H_
