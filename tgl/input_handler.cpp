#include "tgl/globals.h"
#include "tgl/input_handler.h"

namespace tgl
{

InputHandler::InputHandler():
	hold_threshold(0.2)
{
	key_glfw_enum['w'] = GLFW_KEY_W;
	key_glfw_enum['s'] = GLFW_KEY_S;
	key_glfw_enum['d'] = GLFW_KEY_D;
	key_glfw_enum['a'] = GLFW_KEY_A;
	key_glfw_enum['e'] = GLFW_KEY_E;
	key_glfw_enum[' '] = GLFW_KEY_SPACE;
	key_glfw_enum[1] = GLFW_MOUSE_BUTTON_LEFT;
	key_glfw_enum[2] = GLFW_MOUSE_BUTTON_RIGHT;
	key_glfw_enum['1'] = GLFW_KEY_1;
	key_glfw_enum['1' + 1] = GLFW_KEY_2;
	key_glfw_enum['1' + 2] = GLFW_KEY_3;
	key_glfw_enum['1' + 3] = GLFW_KEY_4;
	key_glfw_enum['1' + 4] = GLFW_KEY_5;

	for (auto key : key_states)
	{
		key_held[key.first] = false;
		key_states[key.first] = false;
		held_time[key.first] = -1;
	}

    set_cursor_enabled(false);
}

void InputHandler::tick(double time_delta)
{
#ifdef _TGL_SERVER
#elif defined(_TGL_CLIENT)
	glfwGetCursorPos(global::window, &mouse_x, &mouse_y);
	for (auto key : key_states)
	{
		if (glfwGetKey(global::window, key_glfw_enum[key.first]) == GLFW_PRESS)
		{
			if (key_press[key.first] == false)
			{
				key_press[key.first] = true;
			}
			else
			{
				key_press[key.first] = false;
			}
			held_time[key.first] += time_delta;
			key_states[key.first] = true;
			if (held_time[key.first] > hold_threshold)
			{
				key_held[key.first] = true;
			}
		}
		else
		{
			key_press[key.first] = false;
			key_states[key.first] = false;
			key_held[key.first] = false;
		}
	}
	if (glfwGetMouseButton(global::window, key_glfw_enum[1]) == GLFW_PRESS)
	{
		if (key_press[1] == false)
		{
			key_press[1] = true;
		}
		else
		{
			key_press[1] = false;
		}
		held_time[1] += time_delta;
		key_states[1] = true;
		if (held_time[1] > hold_threshold)
		{
			key_held[1] = true;
		}
	}
	else
	{
		key_press[1] = false;
		key_states[1] = false;
		key_held[1] = false;
	}
	if (glfwGetMouseButton(global::window, key_glfw_enum[2]) == GLFW_PRESS)
	{
		if (key_press[2] == false)
		{
			key_press[2] = true;
		}
		else
		{
			key_press[2] = false;
		}
		held_time[2] += time_delta;
		key_states[2] = true;
		if (held_time[2] > hold_threshold)
		{
			key_held[2] = true;
		}
	}
	else
	{
		key_press[2] = false;
		key_states[2] = false;
		key_held[2] = false;
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
