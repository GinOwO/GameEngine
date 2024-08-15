#pragma once

#include <graphics/Shader.h>
#include <graphics/Material.h>

#include <math/Matrix4f.h>

class BasicShader : public Shader {
    public:
	BasicShader();
	BasicShader(const std::string &vertexPath,
		    const std::string &fragmentPath);

	void update_uniforms(const Matrix4f &world_matrix,
			     const Matrix4f &projected_matrix,
			     const Material &material);
};