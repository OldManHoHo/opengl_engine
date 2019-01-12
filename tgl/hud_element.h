#pragma once
#ifndef TGL_HUD_ELEMENT_H_
#define TGL_HUD_ELEMENT_H_

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "tgl/material.h"
#include "tgl/shader.h"

namespace tgl
{

class HudElement
{
 public:
    bool texture_active;
    GLfloat height;
    GLfloat width;
    glm::vec3 color;
    glm::vec2 pos;
    std::vector <GLfloat> params;
    std::vector <HudElement*> sub_elements;

    tgl::Texture * tex;
    glm::vec2 top_left_tex_offset;
    glm::vec2 bottom_right_tex_offset;
    tgl::Material mat;
    tgl::Shader * hud_shader_f;
    tgl::Shader * hud_shader_v;

    HudElement(GLfloat in_width,
               GLfloat in_height,
               glm::vec2 in_pos,
               glm::vec3 in_color,
               char * texture_file = nullptr,
               int top_left_tex_offset_x = 0,
               int top_left_tex_offset_y = 0,
               int bottom_right_tex_offset_x = 0,
               int bottom_right_tex_offset_y = 0);

    GLfloat * get_params();
    void set_offsets(glm::vec2 top_left, glm::vec2 bottom_right);
};

}  // namespace tgl

#endif  // TGL_HUD_ELEMENT_H_
