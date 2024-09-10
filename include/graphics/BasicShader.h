#pragma once

#include <graphics/Shader.h>
#include <graphics/Material.h>

#include <math/Matrix4f.h>

class BasicShader : public Shader {
	BasicShader();

    public:
	BasicShader(const BasicShader &) = delete;
	BasicShader &operator=(const BasicShader &) = delete;

	static BasicShader &get_instance();

	void load_shader(const std::string &vertex_path,
			 const std::string &fragment_path);

	void update_uniforms(const Matrix4f &world_matrix,
			     const Matrix4f &projected_matrix,
			     const Material &material) override;
};