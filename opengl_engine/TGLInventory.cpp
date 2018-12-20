#include <iostream>

#include "TGLInventory.h"



int block_place_range = int(iid_sand_block) + 1;

e_block_type item_id_to_block_type(TGLItemId item_id)
{
	if (item_id < block_place_range && item_id != none)
	{
		return static_cast<e_block_type>(item_id);
	}
	return bt_invalid;
}

TGLItemId block_type_to_item_id(e_block_type in_block_type)
{
	return static_cast<TGLItemId>(in_block_type);
	return none;
}

TGLInventoryItem::TGLInventoryItem(TGLItemId in_type, unsigned int in_quantity) :
	quantity(in_quantity),
	type(in_type)
{   }

bool TGLInventoryItem::operator== (const TGLInventoryItem& item_b)
{
	return item_b.type == type && item_b.quantity == quantity;
}

bool TGLInventoryItem::operator!= (const TGLInventoryItem& item_b)
{
	return item_b.type != type || item_b.quantity != quantity;
}

hit_properties TGLInventoryItem::get_hit_properties()
{
	return 1.0;
}

TGLInventoryItem TGLInventory::no_item(none);

TGLInventory::TGLInventory(int in_x_size, int in_y_size) :
	items(in_x_size*in_y_size, nullptr),
	x_size(in_x_size),
	y_size(in_y_size)
{
	set_item(0, 0, pickaxe, 1);
	set_item(1, 0, iid_dirt_block, 10);
}

std::vector <TGLInventoryItem*>& TGLInventory::get_items()
{
	return items;
}

void TGLInventory::set_item(unsigned int in_x, unsigned int in_y, TGLItemId in_type, unsigned int in_quantity)
{
	items[in_y*x_size + in_x] = new TGLInventoryItem(in_type, in_quantity);
}

TGLInventoryItem * TGLInventory::get_item(unsigned int in_x, unsigned int in_y)
{
	return items[in_y*x_size + in_x];
}

// Move an item from on x,y position to another in the inventory.
// If the destination space is occupied, the move will fail and return false.
bool TGLInventory::move_item(unsigned int src_x, unsigned int src_y, unsigned int dest_x, unsigned int dest_y)
{
	bool retval = false;
	TGLInventoryItem * dest = get_item(dest_x, dest_y);
	TGLInventoryItem * src = get_item(src_x, src_y);
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
bool TGLInventory::delete_item(unsigned int in_x, unsigned int in_y)
{
	bool retval = false;
	TGLInventoryItem * to_delete = get_item(in_x, in_y);
	if (to_delete != nullptr)
	{
		delete items[in_y*x_size + in_x];
		items[in_y*x_size + in_x] = nullptr;
		retval = true;
	}
	else
	{
		retval = false;
	}
	return retval;
}

bool TGLInventory::change_quantity(TGLItemId in_type, int in_quantity)
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
		TGLInventoryItem * new_item_p;
		for (int i = 0; i < items.size(); ++i)
		{
			if (items[i] == nullptr)
			{
				items[i] = new TGLInventoryItem(in_type, in_quantity);
				break;
			}
		}
	}
	return done;
}

void TGLInventory::print_inventory()
{
	for (unsigned int i = 0; i < y_size; ++i)
	{
		for (unsigned int j = 0; j < x_size; ++j)
		{
			if (get_item(j, i) != nullptr)
			{
				std::cout << get_item(j, i)->type << ", " << get_item(j, i)->quantity << ";\t";
			}
			else
			{
				std::cout << "NULL" << ";\t";
			}
		}
		std::cout << "\n";
	}
	printf("\nDONE\n");
}

int main_inventory()
{
	TGLInventory test_inventory(10, 5);

	std::vector <TGLInventoryItem*>& item_refs = test_inventory.get_items();
	test_inventory.print_inventory();
	test_inventory.set_item(9, 4, iid_sand_block, 100);
	test_inventory.print_inventory();
	test_inventory.change_quantity(iid_sand_block, -100);
	test_inventory.print_inventory();
	test_inventory.delete_item(0, 0);
	test_inventory.print_inventory();
	test_inventory.change_quantity(iid_stone_block, 1);
	test_inventory.print_inventory();
	test_inventory.change_quantity(iid_stone_block, 4);
	test_inventory.print_inventory();
	return 1;
}