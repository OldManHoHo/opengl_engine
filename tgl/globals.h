#ifndef TGL_GLOBALS_H_
#define TGL_GLOBALS_H_

#include "tgl/tgl_gl.h"

namespace tgl
{
    
namespace global
{

#ifdef _TGL_CLIENT
extern GLFWwindow * window;
#endif
extern int window_height;
extern int window_width;
extern bool server_processing;

}  // namespace global

}  // namespace tgl

#endif  // TGL_GLOBALS_H_
