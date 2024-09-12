#pragma once

#include <math/Matrix4f.h>
#include <math/Transform.h>

#include <core/Camera.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>

class BasicShader : public Shader {
	BasicShader();

    public:
	BasicShader(const BasicShader &) = delete;
	BasicShader &operator=(const BasicShader &) = delete;

	static BasicShader &get_instance();

	void load_shader(const std::string &vertex_path,
			 const std::string &fragment_path);

	void update_uniforms(const Transform &transform,
			     const Material &material) override;
};