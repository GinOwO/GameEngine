#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <math/Matrix4f.h>
#include <math/Vector3f.h>
#include <math/Transform.h>

#include <components/BaseCamera.h>

#include <graphics/Material.h>
#include <graphics/Specular.h>
#include <graphics/resource_management/ShaderResource.h>

#include <string>
#include <memory>
#include <utility>
#include <unordered_map>

class Shader {
    protected:
	Transform const *transform;

    private:
	struct __pair_hash {
		template <class T1, class T2>
		std::size_t operator()(const std::pair<T1, T2> &pair) const
		{
			std::size_t hash1 = std::hash<T1>{}(pair.first);
			std::size_t hash2 = std::hash<T2>{}(pair.second);
			// Combine the two hash values
			return hash1 ^ (hash2 << 1);
		}
	};
	std::shared_ptr<ShaderResource> shader_resource;
	static std::unordered_map<std::pair<std::string, std::string>,
				  std::weak_ptr<ShaderResource>, __pair_hash>
		shader_cache;

	std::string read_shader(const std::string &filepath) const;

	GLuint create_shader_module(const std::string &shader_source,
				    GLuint module_type) const;

    protected:
	void load(const std::string &vertex_filepath,
		  const std::string &fragment_filepath);

    public:
	Shader();

	GLuint get_program() const noexcept;

	void use_program() const noexcept;

	void add_uniform(const std::string &uniform);

	GLuint get_uniform(const std::string &uniform) const;

	void set_uniform(const std::string &uniform, int32_t value);

	void set_uniform(const std::string &uniform, float value);

	void set_uniform(const std::string &uniform, Vector3f value);

	void set_uniform(const std::string &uniform, Matrix4f value);

	void set_uniform(const std::string &uniform, const Specular &specular);

	void set_uniform(const std::string &uniform, const Matrix4f &matrix,
			 int32_t count);

	virtual void update_uniforms(Transform *transform,
				     const Material &material) = 0;
};
