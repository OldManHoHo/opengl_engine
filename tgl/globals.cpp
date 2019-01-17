#include "tgl/globals.h"

namespace tgl
{
    
namespace global
{

#ifdef _TGL_CLIENT
GLFWwindow * window = nullptr;
#endif
bool server_processing = false;

}  // namespace global

}  // namespace tgl