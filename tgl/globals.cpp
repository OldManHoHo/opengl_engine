#include "tgl/globals.h"

namespace tgl
{
    
namespace global
{

#ifdef _TGL_CLIENT
GLFWwindow * window = nullptr;
int window_height = 200;
int window_width = 200;
#endif
bool server_processing = false;

}  // namespace global

}  // namespace tgl