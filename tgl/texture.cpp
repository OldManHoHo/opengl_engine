#include "tgl/texture.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "tgl/stb_image.h"

namespace tgl
{

GLuint Texture::texture_count = 0;

Texture::Texture(const char * filename)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        printf("GL ERROR Texture init: %d\n", err);
    }
    glGenTextures(1, &texture);

    texture_id = texture_count;
    texture_count += 1;

    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options
    // (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load and generate the texture
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 4);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     width,
                     height,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

Texture::Texture(FT_Bitmap * bitmap, int in_x, int in_y)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        printf("GL ERROR Texture init: %d\n", err);
    }
    glGenTextures(1, &texture);

    texture_id = texture_count;
    texture_count += 1;

    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options
    // (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    width = bitmap->width;
    height = bitmap->rows;

    bool fake = false;
   // width = 10;
    //height = 10;
    char data[10 * 10 * 3];
    for (int i = 0; i < 10 * 10*3; ++i)
    {
        data[i] = 0;
    }

    // load and generate the texture
    if (!fake)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGBA,
            bitmap->width,
            bitmap->rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            bitmap->buffer);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGB,
            10,
            10,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            data);
        glGenerateMipmap(GL_TEXTURE_2D);
        while ((err = glGetError()) != GL_NO_ERROR)
        {
            printf("GL ERROR fake texture init: %d\n", err);
        }
    }
}


Texture::~Texture()
{
}

GLuint Texture::get_name()
{
    return texture;
}

}  // namespace tgl
