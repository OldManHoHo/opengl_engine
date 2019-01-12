#include "tgl/shader.h"

#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

namespace tgl
{

Shader::Shader(const char * shader_file, GLuint shader_type)
{
    load_shader(shader_file, shader_type);
}

Shader::~Shader()
{
}

void Shader::load_shader(const char * shader_file, GLuint shader_type)
{
    std::ifstream t(shader_file);
    std::string str;
    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());

    const GLchar *source = (const GLchar *)str.c_str();
    printf("%s\n", source);
    shader_object = glCreateShader(shader_type);

    glShaderSource(shader_object, 1, &source, NULL);
    glCompileShader(shader_object);

    int success;
    glGetShaderiv(shader_object, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader_object, 512, NULL, infoLog);
        std::cout <<
            "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
            infoLog << "\n";
    }
}

GLuint Shader::get_shader_name()
{
    return shader_object;
}

}  // namespace tgl
