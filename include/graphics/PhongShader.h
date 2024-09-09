#pragma once

#include <graphics/Shader.h>
#include <graphics/Material.h>
#include <graphics/BaseLight.h>
#include <graphics/DirectionalLight.h>

#include <math/Matrix4f.h>
#include <math/Vector3f.h>

class PhongShader : public Shader {
	Vector3f ambient_light{ 0.8, 0.8, 0.8 };
	DirectionalLight directional_light{ BaseLight{ { 1, 1, 1 }, 0 },
					    { 0, 0, 0 } };

    public:
	PhongShader();
	PhongShader(const std::string &vertexPath,
		    const std::string &fragmentPath);

	void update_uniforms(const Matrix4f &world_matrix,
			     const Matrix4f &projected_matrix,
			     const Material &material,
			     const Vector3f &camera_position);

	Vector3f &get_ambient_light() noexcept;
	void set_ambient_light(const Vector3f &ambient_light) noexcept;

	DirectionalLight &get_directional_light() noexcept;
	void set_directional_light(
		const DirectionalLight &directional_light) noexcept;

	using Shader::set_uniform;
	void set_uniform(const std::string &uniform,
			 const BaseLight &base_light) noexcept;
	void set_uniform(const std::string &uniform,
			 const DirectionalLight &directional_light) noexcept;
	void set_uniform(const std::string &uniform,
			 const Specular &specular) noexcept;
};