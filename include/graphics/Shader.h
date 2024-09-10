#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <math/Matrix4f.h>
#include <math/Vector3f.h>
#include <graphics/Material.h>

#include <string>
#include <unordered_map>

class Shader {
    private:
	GLuint shader_program;
	std::unordered_map<std::string, GLuint> uniforms;

	std::string read_shader(const std::string &filepath) const;

	GLuint create_shader_module(const std::string &shader_source,
				    GLuint module_type) const;

    protected:
	void load(const std::string &vertex_filepath,
		  const std::string &fragment_filepath);

    public:
	Shader();

	void delete_program() noexcept;
	GLuint get_program() const noexcept;

	void use_program() const noexcept;

	void add_uniform(const std::string &uniform);
	GLuint get_uniform(const std::string &uniform) const noexcept;

	void set_uniform(const std::string &uniform, int value) noexcept;
	void set_uniform(const std::string &uniform, float value) noexcept;
	void set_uniform(const std::string &uniform, Vector3f value) noexcept;
	void set_uniform(const std::string &uniform, Matrix4f value) noexcept;
};