#pragma once

#include <math/Matrix4f.h>
#include <math/Transform.h>

#include <components/BaseCamera.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>

#include <components/BaseLight.h>

class ForwardDirectional : public Shader {
	ForwardDirectional();

    public:
	ForwardDirectional(const ForwardDirectional &) = delete;
	ForwardDirectional &operator=(const ForwardDirectional &) = delete;

	static ForwardDirectional &get_instance();

	void load_shader();

	using Shader::set_uniform;

	void set_uniform(const std::string &uniform,
			 const BaseLight &base_light) noexcept;

	void update_uniforms(Transform *transform,
			     const Material &material) override;
};
