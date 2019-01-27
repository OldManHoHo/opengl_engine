#include <iostream>

#include "tgl/inventory.h"

namespace tgl
{

InventoryItem::InventoryItem(ItemId in_type, unsigned int in_quantity) :
    quantity(in_quantity),
    type(in_type)
{   }

bool InventoryItem::operator== (const InventoryItem& item_b)
{
    return item_b.type == type && item_b.quantity == quantity;
}

bool InventoryItem::operator!= (const InventoryItem& item_b)
{
    return item_b.type != type || item_b.quantity != quantity;
}

InventoryItem Inventory::no_item(none);

Inventory::Inventory(int in_size) :
    items(in_size, nullptr),
    size(in_size)
{
    set_item(0, pickaxe, 1);
    set_item(1, iid_dirt_block, 10);
}

std::vector <InventoryItem*>& Inventory::get_items()
{
    return items;
}

void Inventory::set_item(unsigned int in_index,
                         ItemId in_type,
                         unsigned int in_quantity)
{
    items[in_index] = new InventoryItem(in_type, in_quantity);
}

InventoryItem * Inventory::get_item(unsigned int in_index)
{
    return items[in_index];
}

// Move an item from one position to another in the inventory.
// If the destination space is occupied, the move will fail and return false.
bool Inventory::move_item(unsigned int src_index,
                          unsigned int dest_index)
{
    bool retval = false;
    InventoryItem * dest = get_item(dest_index);
    InventoryItem * src = get_item(src_index);
    if (dest == nullptr)
    {
        dest = src;
        src = nullptr;
        retval = true;
    }
    else
    {
        retval = false;
    }
    return retval;
}

// Delete an item from the inventory. If the space to delete is empty,
// the delete will fail and return false.
bool Inventory::delete_item(unsigned int in_index)
{
    bool retval = false;
    InventoryItem * to_delete = get_item(in_index);
    if (to_delete != nullptr)
    {
        delete items[in_index];
        items[in_index] = nullptr;
        retval = true;
    }
    else
    {
        retval = false;
    }
    return retval;
}

bool Inventory::change_quantity(ItemId in_type, int in_quantity)
{
    bool done = false;
    bool new_item = true;
    for (int i = 0; i < items.size(); ++i)
    {
        if (items[i] != nullptr)
        {
            if (items[i]->type == in_type)
            {
                new_item = false;
                if (items[i]->quantity + in_quantity >= 0)
                {
                    items[i]->quantity += in_quantity;
                    if (items[i]->quantity == 0)
                    {
                        delete items[i];
                        items[i] = nullptr;
                    }
                    done = true;
                    break;
                }
            }
        }
    }
    if (new_item && in_quantity > 0)
    {
        InventoryItem * new_item_p;
        for (int i = 0; i < items.size(); ++i)
        {
            if (items[i] == nullptr)
            {
                items[i] = new InventoryItem(in_type, in_quantity);
                break;
            }
        }
    }
    return done;
}

void Inventory::print_inventory()
{
    for (unsigned int i = 0; i < size; ++i)
    {
            if (get_item(i) != nullptr)
            {
                std::cout <<
                    get_item(i)->type <<
                    ", " <<
                    get_item(i)->quantity <<
                    ";\n";
            }
            else
            {
                std::cout << "NULL" << ";\n";
            }

    }
    printf("\nDONE\n");
}

void Inventory::swap_items(int index_1, int index_2)
{
	InventoryItem * swapper = items[index_1];
	items[index_1] = items[index_2];
	items[index_2] = swapper;
}

int main_inventory()
{
    Inventory test_inventory(50);

    std::vector <InventoryItem*>& item_refs = test_inventory.get_items();
    test_inventory.print_inventory();
    test_inventory.set_item(36, iid_sand_block, 100);
    test_inventory.print_inventory();
    test_inventory.change_quantity(iid_sand_block, -100);
    test_inventory.print_inventory();
    test_inventory.delete_item(0);
    test_inventory.print_inventory();
    test_inventory.change_quantity(iid_stone_block, 1);
    test_inventory.print_inventory();
    test_inventory.change_quantity(iid_stone_block, 4);
    test_inventory.print_inventory();
    return 1;
}

}  // namespace tgl
