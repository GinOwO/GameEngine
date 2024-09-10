#include <graphics/BasicShader.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>

#include <iostream>

BasicShader::BasicShader()
	: Shader()
{
}

BasicShader &BasicShader::get_instance()
{
	static BasicShader instance;
	return instance;
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
	material.get_texture().bind();

	this->set_uniform("transform", projected_matrix);
	this->set_uniform("color", material.get_color());
}