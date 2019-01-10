#ifndef TGL_INPUTHANDLER_H_
#define TGL_INPUTHANDLER_H_

#include <map>

#include "tgl/tgl_gl.h"

class InputHandler
{
public:
    std::map <char, bool> key_states;
    double mouse_x, mouse_y;
    InputHandler();
    void tick(double time_delta);
	void generate_input();
};

#endif