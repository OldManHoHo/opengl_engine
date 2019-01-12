#pragma once
#ifndef TGL_PLAYER_H_
#define TGL_PLAYER_H_

#include <vector>

#include "tgl/camera.h"
#include "tgl/hud_element.h"
#include "tgl/input_handler.h"
#include "tgl/inventory.h"
#include "tgl/mesh.h"

namespace tgl
{

class Player : public tgl::Camera
{
    tgl::Mesh * debug_block;
    tgl::InventoryItem blank_item;

 protected:
    InputHandler input_handler;

 public:
    glm::vec3 forward_vec;
    double multi_press_threshold;
    std::vector <tgl::HudElement*> hud;

    tgl::Inventory inventory;
    tgl::InventoryItem * equipped_item;
    tgl::HudElement * inventory_hud;
    char equipped_index;

    float y_angle;
    float x_angle;

    glm::vec3 crosshair;

    bool hitting_bool;
    glm::vec3 hitting;

    Player();
    ~Player();
    void tick(double time_delta);
    void set_hitting(glm::vec3 in_hitting);
    glm::vec3 get_hitting();
    void add_hud(tgl::HudElement * in_hud);
    tgl::InventoryItem& get_equipped();
    bool set_equipped(int item_num);
    bool change_inventory_amount(tgl::ItemId item_type, int in_amount);
    void generate_input_msg(std::vector <char> & input_msg);
    void apply_input_msg(std::vector <char> & input_msg);
};

}  // namespace tgl

#endif  // TGL_PLAYER_H_
