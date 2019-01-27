#include "tmc/hud/button.h"

namespace tmc
{
namespace hud
{

Button::Button(
                  std::string in_button_text,
                  int in_pos_x, int in_pos_y,
                  int in_width, int in_height,
                  glm::vec3 in_color):
    button_text(in_button_text),
    tgl::HudElement(in_width,
            in_height,
            glm::vec2(in_pos_x, in_pos_y),
            in_color)
{
    tgl::HudElement * button_text_element;
    button_text_element = new tgl::HudElement(
                30,
                30,
                glm::vec2(5, 5),
                glm::vec3(0, 0, 0),
                std::string(button_text),
                0,
                0,
                0,
                0);
    sub_elements.push_back(button_text_element);
}

void Button::on_click()
{
}

void Button::on_click_release()
{
}
    
}  // namespace hud
}  // namespace tmc