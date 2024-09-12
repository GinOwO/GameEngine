#pragma once

#include <vector>
#include <iostream>

#include <math/Matrix4f.h>
#include <math/Vector3f.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>
#include <graphics/BaseLight.h>
#include <graphics/SpotLight.h>
#include <graphics/PointLight.h>
#include <graphics/DirectionalLight.h>

class PhongShader : public Shader {
    public:
	PhongShader(const PhongShader &) = delete;
	PhongShader &operator=(const PhongShader &) = delete;

	static PhongShader &get_instance();

    private:
	Vector3f ambient_light{ 0.8, 0.8, 0.8 };
	DirectionalLight directional_light{ BaseLight{ "#FFF", 0 },
					    { 0, 0, 0 } };

	const int MAX_POINT_LIGHTS = 4;
	const int MAX_SPOT_LIGHTS = 4;

	PhongShader();

    public:
	std::vector<PointLight> point_lights;
	std::vector<SpotLight> spot_lights;

	void load_shaders(const std::string &vertexPath,
			  const std::string &fragmentPath);

	void update_uniforms(const Transform &transform,
			     const Material &material) override;

	Vector3f &get_ambient_light() noexcept;
	void set_ambient_light(const Vector3f &ambient_light) noexcept;

	DirectionalLight &get_directional_light() noexcept;
	void set_directional_light(
		const DirectionalLight &directional_light) noexcept;

	void set_point_lights(const std::vector<PointLight> &point_lights);
	void set_spot_lights(const std::vector<SpotLight> &spot_lights);

	using Shader::set_uniform;
	void set_uniform(const std::string &uniform,
			 const BaseLight &base_light) noexcept;
	void set_uniform(const std::string &uniform,
			 const DirectionalLight &directional_light) noexcept;
	void set_uniform(const std::string &uniform,
			 const Specular &specular) noexcept;
	void set_uniform(const std::string &uniform,
			 const PointLight &point_light) noexcept;
	void set_uniform(const std::string &uniform,
			 const SpotLight &spot_light) noexcept;
};