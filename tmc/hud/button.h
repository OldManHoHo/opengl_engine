#ifndef TMC_HUD_BUTTON_H_
#define TMC_HUD_BUTTON_H_

#include <string>

#include <tgl/hud_element.h>
#include <tgl/texture.h>

namespace tmc
{
namespace hud
{
    
class Button : public tgl::HudElement
{
    tgl::Texture * on_tex;
    tgl::Texture * off_tex;
    std::string button_text;
    
 public:   
    Button(
        std::string in_button_text,
        int in_pos_x, int in_pos_y,
        int in_width, int in_height,
        glm::vec3 in_color);
    void on_click();
    void on_click_release();
};
    
}  // namespace hud
}  // namespace tmc

#endif  // TMC_HUD_BUTTON_H_