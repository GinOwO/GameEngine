#include <graphics/PhongShader.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>
#include <graphics/BaseLight.h>
#include <graphics/DirectionalLight.h>

#include <math/Matrix4f.h>
#include <math/Vector3f.h>

#include <core/RenderUtil.h>

#include <iostream>

PhongShader::PhongShader()
	: Shader()
{
}

PhongShader::PhongShader(const std::string &vertexPath,
			 const std::string &fragmentPath)
	: Shader(vertexPath, fragmentPath)
{
	this->add_uniform("transform");
	this->add_uniform("transform_projected");
	this->add_uniform("base_color");

	this->add_uniform("ambient_light");
	this->add_uniform("directional_light.base_light.color");
	this->add_uniform("directional_light.base_light.intensity");
	this->add_uniform("directional_light.direction");

	this->add_uniform("specular.intensity");
	this->add_uniform("specular.exponent");
	this->add_uniform("eyePos");
}

void PhongShader::update_uniforms(const Matrix4f &world_matrix,
				  const Matrix4f &projected_matrix,
				  const Material &material,
				  const Vector3f &camera_position)
{
	if (material.get_texture().get_id() > 0) {
		material.get_texture().bind();
	} else {
		RenderUtil::unbind_textures();
	}

	this->set_uniform("transform_projected", projected_matrix);
	this->set_uniform("transform", world_matrix);

	this->set_uniform("ambient_light", ambient_light);
	this->set_uniform("directional_light", directional_light);

	this->set_uniform("base_color", material.get_color());
	this->set_uniform("specular", material.get_specular());
	this->set_uniform("eyePos", camera_position);
}

Vector3f &PhongShader::get_ambient_light() noexcept
{
	return ambient_light;
}

void PhongShader::set_ambient_light(const Vector3f &ambient_light) noexcept
{
	this->ambient_light = Vector3f(ambient_light);
}

DirectionalLight &PhongShader::get_directional_light() noexcept
{
	return directional_light;
}

void PhongShader::set_directional_light(
	const DirectionalLight &directional_light) noexcept
{
	this->directional_light.base_light = directional_light.base_light;
	this->directional_light.direction =
		directional_light.direction.normalize();
}

void PhongShader::set_uniform(const std::string &uniform,
			      const BaseLight &base_light) noexcept
{
	this->set_uniform(uniform + ".color", base_light.color);
	this->set_uniform(uniform + ".intensity", base_light.intensity);
}

void PhongShader::set_uniform(const std::string &uniform,
			      const DirectionalLight &directional_light) noexcept
{
	set_uniform(uniform + ".base_light", directional_light.base_light);
	set_uniform(uniform + ".direction", directional_light.direction);
}

void PhongShader::set_uniform(const std::string &uniform,
			      const Specular &specular) noexcept
{
	set_uniform(uniform + ".intensity", specular.intensity);
	set_uniform(uniform + ".exponent", specular.exponent);
}