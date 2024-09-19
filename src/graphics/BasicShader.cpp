#include <graphics/BasicShader.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>

#include <core/RenderUtil.h>

#include <iostream>

BasicShader::BasicShader()
	: Shader()
{
}

void BasicShader::load_shader(const std::string &vertex_path,
			      const std::string &fragment_path)
{
	this->load(vertex_path, fragment_path);
	this->add_uniform("transform");
	this->add_uniform("color");
}

void BasicShader::update_uniforms(const Matrix4f &world_matrix,
				  const Matrix4f &projected_matrix,
				  const Material &material)
{
	if (material.get_texture().get_id() > 0) {
		material.get_texture().bind();
	} else {
		RenderUtil::unbind_textures();
	}

	this->set_uniform("transform", projected_matrix);
	this->set_uniform("color", material.get_color());
}