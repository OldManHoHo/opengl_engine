#ifndef TMC_HUD_BUTTON_H_
#define TMC_HUD_BUTTON_H_

namespace tmc
{
namespace hud
{
    
class Button : public tgl::HudElement
{
    tgl::Texture * on_tex;
    tgl::Texture * off_tex;
    std::string button_text;
    const int (&)[] on_press;
    
 public:   
    Button();
    void on_click(const int (&)[1] in_on_press,
                  std::string in_button_text,
                  int in_pos_x, int in_pos_y,
                  int in_width, int in_height
                  glm::vec3 in_color);
    void on_click_release();
};
    
}  // namespace hud
}  // namespace tmc

#endif  // TMC_HUD_BUTTON_H_