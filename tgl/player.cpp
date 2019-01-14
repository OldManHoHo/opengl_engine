#include "tgl/player.h"

#include <stdio.h>

#include "glm/gtx/matrix_decompose.hpp"
#include "tgl/tgl_gl.h"
#include "tgl/base.h"
#include "tgl/useful_structures.h"

extern tgl::Base gl_base;  // TODO(Teddy Walsh): Get rid of this global

namespace tgl
{

Player::Player() :
    inventory(10, 10),
    multi_press_threshold(0.25),
    blank_item(tgl::ItemId::none, 0),
    equipped_index(0)
{
#ifdef _TGL_CLIENT
    glfwSetInputMode(gl_base.get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif
    x_angle = 0;
    y_angle = 0;

    set_view(glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 5.0f, -5.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)));
    tgl::Bounds * new_bounds = new tgl::BlockBounds(0.925, 1.85, 0.925);
    set_bounds(new_bounds);
    mass = 68;
    hitting = glm::vec3(0, 300, 0);
}

Player::~Player()
{
}

extern tgl::Actor debug_actor;

void Player::tick(double time_delta)
{
#ifdef _TGL_SERVER
    get_view();
#endif
    input_handler.tick(time_delta);

    static float debug_rot = 0.0;
    static float time_passed = 0.0;
    time_passed += time_delta;
    debug_rot +=  5;
    glm::vec3 up_vector(0.0, 1.0, 0.0);
    up_vector = glm::mat3(get_rot())*up_vector;
    glm::vec3 x_vector(1.0, 0.0, 0.0);
    // glfwGetCursorPos(gl_base.get_window(), &xpos, &ypos);
    double xpos, ypos;
    xpos = input_handler.mouse_x;
    ypos = input_handler.mouse_y;
    x_angle += ypos*3.14159 / 5000;
    while (x_angle > 3.14159)
    {
        x_angle -= 2 * 3.14159;
    }
    while (x_angle < -3.14159)
    {
        x_angle += 2 * 3.14159;
    }
    y_angle += xpos*3.14159 / 5000;
    while (y_angle > 3.14159)
    {
        y_angle -= 2 * 3.14159;
    }
    while (y_angle < -3.14159)
    {
        y_angle += 2 * 3.14159;
    }
#ifdef _TGL_CLIENT
    set_rot(glm::mat4(1.0));
#endif
    // set_rot(glm::quat());

    rotate(-y_angle, glm::vec3(0, 1.0, 0));
    rotate(-x_angle, glm::vec3(0.0, 0.0, 1.0));

    x_vector = glm::mat3(get_rot())*x_vector;

    if (time_passed > 0.5)
    {
        time_passed = 0;
        debug_rot = 0;
        std::cout <<
            "Y POS " <<
            pos.y <<
            ", " <<
            "X POS" <<
            pos.x <<
            ", " <<
            "Z POS" <<
            pos.z <<
            "\n";
    }
    // std::cout <<
    //      "DEBUG Y POS " <<
    //      debug_block->pos.y <<
    //      ", " <<
    //      "X POS" <<
    //      debug_block->pos.x <<
    //      ", " <<
    //      "Z POS" <<
    //      debug_block->pos.z <<
    //      "\n";
#ifdef _TGL_CLIENT
    glfwSetCursorPos(gl_base.get_window(), 0, 0);
#endif

    glm::vec3 forward_vector_crosshair(1.0, 0.0, 0.0);
    forward_vector_crosshair = glm::mat3(get_rot())*forward_vector_crosshair;
    forward_vec = forward_vector_crosshair;
    // forward_vector += pos;
    // forward_vector += glm::vec3(0.0, 0.5, 0);
    crosshair = forward_vector_crosshair;

    if (input_handler.key_states['w'])
    {
        // glm::vec3 forward_vector(time_delta * 50 * sin(-y_angle),
        //                          vel.y, time_delta*50*cos(-y_angle));
        // glm::quat move_rot = glm::quat(0, glm::vec3(0.0, 1.0, 0.0));
        // vel = forward_vector;
        // translate(forward_vector);
        glm::vec3 forward_vector(10.0, 0.0, 0.0);
        forward_vector = glm::mat3(get_rot())*forward_vector;
        forward_vector.y = 0;
        // translate(forward_vector);
        vel.x = forward_vector.x;
        vel.z = forward_vector.z;
        // debug_block->set_pos(glm::vec3(0, 0, 2.0));
    }
    else
    {
        vel.x = 0;
        vel.z = 0;
    }
    if (input_handler.key_states['s'])
    {
        glm::vec3 forward_vector(0.0, 0.0, time_delta*-30);
        forward_vector = forward_vector*glm::mat3(get_rot());
    }
    if (input_handler.key_states[' '])
    {
        if (get_on_ground())
        {
            vel.y += 5;
            if (vel.y > 5)
            {
                vel.y = 5;
            }
        }
    }
    return;
}

void Player::set_hitting(glm::vec3 in_hitting)
{
    hitting = in_hitting;
}

glm::vec3 Player::get_hitting()
{
    return hitting;
}

void Player::add_hud(tgl::HudElement * in_hud)
{
    hud.push_back(in_hud);
}

tgl::InventoryItem& Player::get_equipped()
{
    if (equipped_item != nullptr)
    {
        return *equipped_item;
    }
    else
    {
        return blank_item;
    }
}

bool Player::change_inventory_amount(tgl::ItemId item_type, int in_amount)
{
    return inventory.change_quantity(item_type, in_amount);
}

void Player::generate_input_msg(std::vector <char> & input_msg)
{
    // std::vector <unsigned char> input_msg(1024);
    if (input_msg.size() < 1024)
    {
        input_msg.resize(1024);
    }
    int offset = 0;
    input_msg[offset] = (unsigned char)(tgl::NetMsgType::PlayerInput);
    offset += sizeof(unsigned char);
    input_msg[offset] = equipped_index;
    offset += sizeof(unsigned char);
    auto rot_p = glm::value_ptr(rot);
    memcpy(&input_msg[offset], rot_p, 16*sizeof(GLfloat));
    offset += sizeof(GLfloat)*16;
    unsigned short * key_state_count = (unsigned short*)&input_msg[offset];
    *key_state_count = 0;
    offset += sizeof(unsigned short);
    for (auto key_state : input_handler.key_states)
    {
        input_msg[offset] = key_state.first;
        offset += sizeof(unsigned char);
        input_msg[offset] = (unsigned char)key_state.second;
        offset += sizeof(unsigned char);
        *key_state_count += 1;
        if (key_state.second)
        {
            std::cout << "KEY PRESSED" << "\n";
        }
    }
    input_msg.resize(offset);
}

void Player::apply_input_msg(std::vector <char> & input_msg)
{
    int offset = 0;
    tgl::NetMsgType msg_type = (tgl::NetMsgType)input_msg[offset];
    offset += sizeof(unsigned char);
    equipped_index = input_msg[offset];
    offset += sizeof(unsigned char);
    glm::mat4 new_rot;
    memcpy(glm::value_ptr(new_rot), &input_msg[offset], sizeof(GLfloat)*16);
    rot = new_rot;
    offset += sizeof(GLfloat)*16;
    unsigned short key_state_count = *(unsigned short*)&input_msg[offset];
    offset += sizeof(unsigned short);
    for (int i = 0; i < key_state_count; ++i)
    {
        char key_type = input_msg[offset];
        offset += sizeof(unsigned char);
        bool pressed = static_cast<bool>(input_msg[offset]);
        offset += sizeof(unsigned char);
        if (input_handler.key_states.find(key_type) !=
            input_handler.key_states.end())
        {
            input_handler.key_states[key_type] = pressed;
        }
    }
}

}  // namespace tgl
