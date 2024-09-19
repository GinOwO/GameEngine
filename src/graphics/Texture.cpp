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

// TODO: comments

const std::function<void(void *)> Texture::deleter{ [](void *ptr) {
	delete static_cast<Texture *>(ptr);
} };

std::unordered_map<std::string, std::weak_ptr<TextureResource> >
	Texture::texture_cache{};

/***************************************************************************
 * @brief Default constructor for Texture.
 *
 * Initializes the Texture object with an ID of 0.
 ***************************************************************************/
Texture::Texture() {};

/***************************************************************************
 * @brief Binds the texture for use in rendering.
 *
 * Binds the texture to the current OpenGL context. If the texture ID is -1,
 * no texture is bound.
 ***************************************************************************/
void Texture::bind() const
{
	if (texture_resource->id == -1)
		return;
	glBindTexture(GL_TEXTURE_2D, texture_resource->id);
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
	return this->texture_resource->id;
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
	Texture *texture = new Texture();

	if (Texture::texture_cache.count(file_path)) {
		std::shared_ptr<TextureResource> resource =
			Texture::texture_cache[file_path].lock();
		if (resource) {
			texture->texture_resource = resource;
			return texture;
		}
	}

	if (texture->texture_resource == nullptr) {
		texture->texture_resource = std::make_shared<TextureResource>();
		texture_cache[file_path] = texture->texture_resource;
	}

	int width, height, channels;
	unsigned char *data =
		stbi_load(file_path.c_str(), &width, &height, &channels, 0);

	if (!data) {
		std::cerr << "Failed to load texture: " << file_path << '\n';
		throw std::runtime_error("Failed to load texture");
		throw std::runtime_error("Failed to load texture");
	}

	glGenTextures(1, &texture->texture_resource->id);
	glBindTexture(GL_TEXTURE_2D, texture->texture_resource->id);

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

	return texture;
}

bool Texture::operator==(const Texture &other) const noexcept
{
	return texture_resource->id == other.texture_resource->id;
}

#undef STB_IMAGE_IMPLEMENTATION
