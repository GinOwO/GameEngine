#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <string>

class Texture {
    private:
	GLuint id;

    public:
	Texture();
	Texture(GLuint id);
	GLuint get_id() const noexcept;

	void bind() const;

	static Texture load_texture(const std::string &file_path);
};