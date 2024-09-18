#include <graphics/Texture.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <misc/stb_image.h>

#include <string>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <exception>

const Texture Texture::None = { 0x101010 };
const std::function<void(void *)> Texture::deleter{ [](void *ptr) {
	delete static_cast<Texture *>(ptr);
} };

/***************************************************************************
 * @brief Default constructor for Texture.
 *
 * Initializes the Texture object with an ID of 0.
 ***************************************************************************/
Texture::Texture()
{
	id = 0;
}

/***************************************************************************
 * @brief Constructs a Texture with a specified ID.
 *
 * Initializes the Texture object with the given OpenGL texture ID.
 *
 * @param id The OpenGL texture ID.
 ***************************************************************************/
Texture::Texture(GLuint id)
	: id(id)
{
}

/***************************************************************************
 * @brief Binds the texture for use in rendering.
 *
 * Binds the texture to the current OpenGL context. If the texture ID is -1,
 * no texture is bound.
 ***************************************************************************/
void Texture::bind() const
{
	if (id == -1)
		return;
	glBindTexture(GL_TEXTURE_2D, id);
}

/***************************************************************************
 * @brief Gets the ID of the texture.
 *
 * Retrieves the OpenGL texture ID associated with this Texture object.
 *
 * @return The OpenGL texture ID.
 ***************************************************************************/
GLuint Texture::get_id() const noexcept
{
	return this->id;
}

/***************************************************************************
 * @brief Loads a texture from a file.
 *
 * Loads a texture image from the specified file path and generates an OpenGL
 * texture object.
 *
 * @param file_path The path to the texture image file.
 * @return A Texture object representing the loaded texture.
 * @throws std::runtime_error if the texture fails to load.
 ***************************************************************************/
Texture *Texture::load_texture(const std::string &file_path)
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

	return new Texture(texture);
}

constexpr bool Texture::operator==(const Texture &other) const noexcept
{
	return id == other.id;
}

#undef STB_IMAGE_IMPLEMENTATION
