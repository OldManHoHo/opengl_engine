#include "tmc/hud/button.h"

namespace tmc
{
namespace hud
{

Button::Button(const int (&)[1] in_on_press,
                  std::string in_button_text,
                  int in_pos_x, int in_pos_y,
                  int in_width, int in_height
                  glm::vec3 in_color):
    button_text(in_button_text),
    on_press(in_on_press),
    tgl::HudElement()
{
  
}

void Button::on_click()
{
    
}
    
}  // namespace hud
}  // namespace tmc