#include "tmc/hud/inventory_slot.h"

namespace tmc
{
namespace hud
{

#ifdef _TGL_CLIENT

InventorySlot::InventorySlot(int in_x, int in_y,
                                   int inventory_slot_width,
                                   int inventory_slot_height,
                                   int inventory_slot_border):
    tgl::HudElement(inventory_slot_width,
                inventory_slot_height,
                glm::vec2(in_x, in_y),
                glm::vec3(0.5, 0.5, 0.5))
{
    picture_element =
        new tgl::HudElement(inventory_slot_width - 2*inventory_slot_border,
            inventory_slot_height - 2*inventory_slot_border,
            glm::vec2(inventory_slot_border,
                inventory_slot_border), glm::vec3(0.5, 0.5, 0.5),
            "content/textures/mc.png");
    text_element = new tgl::HudElement(
        30,
        30,
        glm::vec2(0,0),
        glm::vec3(0, 0, 0),
        std::string("AB"),
        0,
        0,
        0,
        0);
    picture_element->sub_elements.push_back(text_element);
    sub_elements.push_back(picture_element);
    
}

void InventorySlot::on_click()
{
}

void InventorySlot::on_click_release()
{
}

void InventorySlot::on_drag()
{
}

#endif  // _TGL_CLIENT

}  // namespace hud
}  // namespace tmc