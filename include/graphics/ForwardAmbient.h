#pragma once

#include <math/Matrix4f.h>
#include <math/Transform.h>

#include <components/BaseCamera.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>

class ForwardAmbient : public Shader {
	ForwardAmbient();

    public:
	ForwardAmbient(const ForwardAmbient &) = delete;
	ForwardAmbient &operator=(const ForwardAmbient &) = delete;

	static ForwardAmbient &get_instance();

	void load_shader();

	void update_uniforms(Transform *transform,
			     const Material &material) override;
};
