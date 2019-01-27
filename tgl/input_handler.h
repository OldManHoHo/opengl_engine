#ifndef TGL_INPUT_HANDLER_H_
#define TGL_INPUT_HANDLER_H_

#include <map>

#include "tgl/tgl_gl.h"

namespace tgl
{

class InputHandler
{
 public:
    std::map <char, bool> key_states;
	std::map <char, bool> key_held;
	std::map <char, double> held_time;
	std::map <char, bool> key_press;
	std::map <char, int> key_glfw_enum;
	double hold_threshold;

    double mouse_x, mouse_y;
    InputHandler();
    void tick(double time_delta);
    void generate_input();
    void set_cursor_enabled(bool cursor_enabled);
    void set_cursor_pos(int in_x, int in_y);
};

}  // namespace tgl

#endif  // TGL_INPUT_HANDLER_H_
