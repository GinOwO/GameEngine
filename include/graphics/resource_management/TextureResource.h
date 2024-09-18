#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

// TODO: comment

class TextureResource {
    public:
	GLuint id; /**< Texture ID. */

	TextureResource();
	~TextureResource();

	void init();
};
