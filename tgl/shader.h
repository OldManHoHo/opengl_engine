#pragma once
#ifndef TGL_SHADER_H_
#define TGL_SHADER_H_


#include "tgl/tgl_gl.h"

namespace tgl
{

class Shader
{
    GLuint shader_object;

 public:
    Shader(const char * shader_file, GLuint shader_type);
    ~Shader();

    void load_shader(const char * shader_file, GLuint shader_type);
    GLuint get_shader_name();
};

}  // namespace tgl

#endif  // TGL_SHADER_H_
