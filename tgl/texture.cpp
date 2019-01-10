#include "tgl/Texture.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace tgl
{

GLuint Texture::texture_count = 0;

Texture::Texture(char * filename)
{
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("GL ERROR: %d\n", err);
	}
	glGenTextures(1, &texture);

	texture_id = texture_count;
	texture_count += 1;
	
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load and generate the texture
	
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 4);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}


Texture::~Texture()
{
}

GLuint Texture::get_name()
{
	return texture;
}

} // namespace tgl