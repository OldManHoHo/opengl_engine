#include "tgl/globals.h"
#include "tgl/input_handler.h"

namespace tgl
{

InputHandler::InputHandler()
{
    key_states['w'] = false;
    key_states['s'] = false;
    key_states['d'] = false;
    key_states['a'] = false;
    key_states['e'] = false;
    key_states[' '] = false;
    key_states[1] = false;
    key_states[2] = false;
    key_states['1'] = false;
    key_states['1'+1] = false;
    key_states['1'+2] = false;
    key_states['1'+3] = false;
    key_states['1'+4] = false;
    set_cursor_enabled(false);
}

void InputHandler::tick(double time_delta)
{
#ifdef _TGL_SERVER
#elif defined(_TGL_CLIENT)
    glfwGetCursorPos(global::window, &mouse_x, &mouse_y);
    if (glfwGetKey(global::window, GLFW_KEY_W) == GLFW_PRESS)
    {
        key_states['w'] = true;
    }
    else
    {
        key_states['w'] = false;
    }
    if (glfwGetKey(global::window, GLFW_KEY_S) == GLFW_PRESS)
    {
        key_states['s'] = true;
    }
    else
    {
        key_states['s'] = false;
    }
    if (glfwGetKey(global::window, GLFW_KEY_A) == GLFW_PRESS)
    {
        key_states['a'] = true;
    }
    else
    {
        key_states['a'] = false;
    }
    if (glfwGetKey(global::window, GLFW_KEY_D) == GLFW_PRESS)
    {
        key_states['d'] = true;
    }
    else
    {
        key_states['d'] = false;
    }
    if (glfwGetKey(global::window, GLFW_KEY_E) == GLFW_PRESS)
    {
        key_states['e'] = true;
    }
    else
    {
        key_states['e'] = false;
    }
    if (glfwGetKey(global::window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        key_states[' '] = true;
    }
    else
    {
        key_states[' '] = false;
    }
    if (glfwGetMouseButton(global::window, GLFW_MOUSE_BUTTON_1) ==
            GLFW_PRESS)
    {
        key_states[1] = true;
    }
    else
    {
        key_states[1] = false;
    }
    if (glfwGetMouseButton(global::window, GLFW_MOUSE_BUTTON_2) ==
            GLFW_PRESS)
    {
        key_states[2] = true;
    }
    else
    {
        key_states[2] = false;
    }
    for (int i = 0; i < 9; ++i)
    {
        if (glfwGetKey(global::window, GLFW_KEY_1 + i) == GLFW_PRESS)
        {
            key_states['1' + i] = true;
        }
        else
        {
            key_states['1' + i] = false;
        }
    }
#endif
}

void InputHandler::generate_input()
{
    // std::vector <unsigned char> message_buf(1024);
}

void InputHandler::set_cursor_enabled(bool cursor_enabled)
{
#ifdef _TGL_CLIENT
    if (cursor_enabled)
    {
        glfwSetInputMode(global::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        glfwSetInputMode(global::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
#endif  // _TGL_CLIENT
}

void InputHandler::set_cursor_pos(int in_x, int in_y)
{
#ifdef _TGL_CLIENT
    glfwSetCursorPos(global::window, in_x, in_y);
#endif  // _TGL_CLIENT
}

}  // namespace tgl
