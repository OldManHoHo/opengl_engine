#ifndef _TGL_INPUTHANDLER
#define _TGL_INPUTHANDLER

#include <map>

#include "tgl_gl.h"

class TGLInputHandler
{
public:
    std::map <char, bool> key_states;
    double mouse_x, mouse_y;
    TGLInputHandler();
    void tick(double time_delta);
	void generate_input();
};

#endif