#pragma once

#include <math/Matrix4f.h>
#include <math/Transform.h>

#include <components/BaseCamera.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>

class ForwardAnimation : public Shader {
    public:
	ForwardAnimation();

	ForwardAnimation(const ForwardAnimation &) = delete;
	ForwardAnimation &operator=(const ForwardAnimation &) = delete;

	static ForwardAnimation &get_instance();

	void load_shader();

	void update_uniforms(Transform *transform,
			     const Material &material) override;
};
