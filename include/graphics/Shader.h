#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <unordered_map>

#include <math/Matrix4f.h>
#include <math/Vector3f.h>
#include <math/Transform.h>

#include <core/Camera.h>

#include <graphics/Material.h>

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
	GLuint get_uniform(const std::string &uniform) const;

	void set_uniform(const std::string &uniform, int value);
	void set_uniform(const std::string &uniform, float value);
	void set_uniform(const std::string &uniform, Vector3f value);
	void set_uniform(const std::string &uniform, Matrix4f value);

	virtual void update_uniforms(const Transform &transform,
				     const Material &material) = 0;
};