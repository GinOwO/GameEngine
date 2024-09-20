#pragma once

#include <math/Matrix4f.h>
#include <math/Transform.h>

#include <components/BaseCamera.h>
#include <components/BaseLight.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>
#include <graphics/Specular.h>

class ForwardAnimated : public Shader {
	ForwardAnimated();

    public:
	ForwardAnimated(const ForwardAnimated &) = delete;
	ForwardAnimated &operator=(const ForwardAnimated &) = delete;

	static ForwardAnimated &get_instance();

	void load_shader();

	void update_uniforms(Transform *transform,
			     const Material &material) override;

	using Shader::set_uniform;

	void set_uniform(const std::string &uniform,
			 const BaseLight &base_light) noexcept;
};
