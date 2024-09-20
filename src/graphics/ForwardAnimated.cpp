#include <graphics/ForwardAnimated.h>

#include <graphics/Shader.h>
#include <graphics/Texture.h>
#include <graphics/Material.h>

#include <components/Camera.h>
#include <components/SharedGlobals.h>
#include <components/BaseLight.h>

#include <iostream>

ForwardAnimated::ForwardAnimated()
	: Shader()
{
	this->load_shader();
}

ForwardAnimated &ForwardAnimated::get_instance()
{
	static ForwardAnimated instance;
	return instance;
}

void ForwardAnimated::load_shader()
{
	this->load("shaders/forwardAnimated.vert",
		   "shaders/forwardAnimated.frag");

	// Common uniforms
	this->add_uniform("model");
	this->add_uniform("MVP");
	this->add_uniform("eyePos");

	// Material uniforms
	this->add_uniform("specular.intensity");
	this->add_uniform("specular.exponent");

	// Bone uniforms
	this->add_uniform("boneTransforms");

	// Light uniforms (assuming directional light for this example)
	this->add_uniform("directional_light.base_light.color");
	this->add_uniform("directional_light.base_light.intensity");
	this->add_uniform("directional_light.direction");
}

void ForwardAnimated::update_uniforms(Transform *transform,
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
	this->set_uniform("eyePos", camera_position);

	// Set specular properties
	this->set_uniform(
		"specular",
		*static_cast<Specular *>(material.get_property("specular")));

	// Set bone transformations
	std::vector<Matrix4f> bone_transforms =
		*static_cast<std::vector<Matrix4f> *>(
			material.get_property("boneTransforms"));
	for (int i = 0; i < bone_transforms.size(); ++i) {
		this->set_uniform("boneTransforms", bone_transforms[i], i);
	}

	// Set light properties
	this->set_uniform("directional_light",
			  *static_cast<BaseLight *>(
				  SharedGlobals::get_instance().active_light));
}

void ForwardAnimated::set_uniform(const std::string &uniform,
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