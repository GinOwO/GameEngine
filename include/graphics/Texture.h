/***************************************************************************
 * @file Texture.h
 *
 * @brief Declares the Texture class for handling textures.
 *
 * This file contains the declaration of the Texture class, which represents
 * a texture used in rendering. It includes methods for binding textures and
 * loading textures from files.
 *
 ***************************************************************************/

#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/resource_management/TextureResource.h>

#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

/***************************************************************************
 * @class Texture
 *
 * @brief Represents a texture used in rendering.
 *
 * The Texture class encapsulates an OpenGL texture object and provides methods
 * for binding the texture and loading it from a file.
 *
 ***************************************************************************/
class Texture {
    private:
	std::shared_ptr<TextureResource> texture_resource;
	static std::unordered_map<std::string, std::weak_ptr<TextureResource> >
		texture_cache;

    public:
	Texture();

	const static Texture None; // TODO: comment
	const static std::function<void(void *)> deleter;

	/***************************************************************************
	 * @brief Gets the texture ID.
	 *
	 * @return The texture ID.
	 ***************************************************************************/
	GLuint get_id() const noexcept;

	/***************************************************************************
	 * @brief Binds the texture for use in rendering.
	 ***************************************************************************/
	void bind() const;

	/***************************************************************************
	 * @brief Loads a texture from a file.
	 *
	 * @param file_path The path to the texture file.
	 * @return The loaded Texture as a shared_ptr.
	 ***************************************************************************/
	static std::shared_ptr<void> load_texture(const std::string &file_path);

	// TODO: comment
	bool operator==(const Texture &other) const noexcept;
};
