#ifndef TMC_HUD_INVENTORY_SLOT_H_
#define TMC_HUD_INVENTORY_SLOT_H_

#include "tgl/hud_element.h"

namespace tmc
{
namespace hud
{

class InventorySlot : public tgl::HudElement
{
 public:
    tgl::HudElement * picture_element;
    tgl::HudElement * text_element;

    InventorySlot(int in_x, int in_y,
                     int inventory_slot_width,
                     int inventory_slot_height,
                     int inventory_slot_border);  
    void on_click();
    void on_click_release();
    void on_drag();
};

}  // namespace hud
}  // namespace tmc

#endif  // TMC_HUD_INVENTORY_SLOT_H_