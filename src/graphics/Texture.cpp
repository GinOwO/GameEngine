#include <graphics/Texture.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <misc/stb_image.h>

#include <string>
#include <iostream>
#include <cstdlib>
#include <exception>

Texture::Texture()
{
	id = 0;
}

Texture::Texture(GLuint id)
	: id(id)
{
}

void Texture::bind() const
{
	if (id == -1)
		return;
	glBindTexture(GL_TEXTURE_2D, id);
}

GLuint Texture::get_id() const noexcept
{
	return this->id;
}

Texture Texture::load_texture(const std::string &file_path)
{
	int width, height, channels;
	unsigned char *data =
		stbi_load(file_path.c_str(), &width, &height, &channels, 0);

	if (!data) {
		std::cerr << "Failed to load texture: " << file_path << '\n';
		throw std::runtime_error("Failed to load texture");
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum format;
	switch (channels) {
	case 1:
		format = GL_RED;
		break;
	case 4:
		format = GL_RGBA;
		break;
	default:
		format = GL_RGB;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
		     GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	return Texture(texture);
}

#undef STB_IMAGE_IMPLEMENTATION