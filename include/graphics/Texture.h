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

#include <string>
#include <functional>

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
	GLuint id; /**< Texture ID. */

    public:
	Texture();
	Texture(GLuint id);

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
	static Texture *load_texture(const std::string &file_path);

	bool operator==(const Texture &other); // TODO: comment
};
