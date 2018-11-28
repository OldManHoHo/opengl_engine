#include "TGLInputHandler.h"

TGLInputHandler::TGLInputHandler()
{
    key_states['w'] = false;
    key_states['s'] = false;
    key_states['d'] = false;
    key_states['a'] = false;
    key_states[' '] = false;
    key_states[1] = false;
    key_states[2] = false;
}

void TGLInputHandler::tick(double time_delta)
{
#ifdef _TGL_SERVER
    
#elif defined(_TGL_CLIENT)
    if (glfwGetKey(gl_base.get_window(), GLFW_KEY_W) == GLFW_PRESS)
	{
	    key_states['w'] = true;
	}
	else
	{
		key_states['w'] = false;
	}
	if (glfwGetKey(gl_base.get_window(), GLFW_KEY_S) == GLFW_PRESS)
	{
	    key_states['s'] = true;
	}
	else
	{
		key_states['s'] = false;
	}
	if (glfwGetKey(gl_base.get_window(), GLFW_KEY_A) == GLFW_PRESS)
	{
	    key_states['a'] = true;
	}
	else
	{
		key_states['a'] = false;
	}
	if (glfwGetKey(gl_base.get_window(), GLFW_KEY_D) == GLFW_PRESS)
	{
	    key_states['d'] = true;
	}
	else
	{
		key_states['d'] = false;
	}
	if (glfwGetKey(gl_base.get_window(), GLFW_KEY_SPACE) == GLFW_PRESS)
	{
	    key_states[' '] = true;
	}
	else
	{
		key_states[' '] = false;
	}
	if (glfwGetMouseButton(gl_base.get_window(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		key_states[1] = true;
	}
	else
	{
	    key_states[1] = false;
	}
	if (glfwGetMouseButton(gl_base.get_window(), GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
	{
		key_states[2] = true;
	}
	else
	{
	    key_states[2] = false;
	}
#endif
}