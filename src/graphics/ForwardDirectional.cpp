#include <graphics/ForwardDirectional.h>

#include <graphics/Shader.h>
#include <graphics/Texture.h>
#include <graphics/Material.h>

#include <components/Camera.h>
#include <core/SharedGlobals.h>
#include <components/BaseLight.h>

#include <iostream>

ForwardDirectional::ForwardDirectional()
	: Shader()
{
	this->load_shader();
}

ForwardDirectional &ForwardDirectional::get_instance()
{
	static ForwardDirectional instance;
	return instance;
}

void ForwardDirectional::load_shader()
{
	this->load("shaders/forwardDirectional.vert",
		   "shaders/forwardDirectional.frag");

	this->add_uniform("model");
	this->add_uniform("MVP");

	this->add_uniform("directional_light.base_light.color");
	this->add_uniform("directional_light.base_light.intensity");
	this->add_uniform("directional_light.direction");

	this->add_uniform("specular.intensity");
	this->add_uniform("specular.exponent");
	this->add_uniform("eyePos");
}

void ForwardDirectional::update_uniforms(Transform *transform,
					 const Material &material)
{
	Camera *camera = static_cast<Camera *>(
		SharedGlobals::get_instance().main_camera);

	Vector3f camera_position =
		camera->get_parent_transform()->get_transformed_position();

	Matrix4f world_matrix = transform->get_transformation();
	Matrix4f projected_matrix = Matrix4f::flip_matrix(
		camera->get_view_projection() * world_matrix);
	world_matrix = Matrix4f::flip_matrix(world_matrix);

	static_cast<Texture *>(material.get_property("diffuse"))->bind();

	this->set_uniform("model", world_matrix);
	this->set_uniform("MVP", projected_matrix);

	this->set_uniform(
		"specular",
		*static_cast<Specular *>(material.get_property("specular")));
	this->set_uniform("eyePos", camera_position);

	this->set_uniform("directional_light",
			  *static_cast<BaseLight *>(
				  SharedGlobals::get_instance().active_light));
}

void ForwardDirectional::set_uniform(const std::string &uniform,
				     const BaseLight &base_light) noexcept
{
	this->set_uniform(uniform + ".base_light.color", base_light.color);
	this->set_uniform(uniform + ".base_light.intensity",
			  base_light.intensity);
	this->set_uniform(uniform + ".direction",
			  base_light.get_parent_transform()
				  ->get_transformed_rotation()
				  .get_forward());
}
