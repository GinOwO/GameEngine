#include <graphics/ForwardAmbient.h>

#include <graphics/Shader.h>
#include <graphics/Texture.h>
#include <graphics/Material.h>

#include <core/SharedGlobals.h>

#include <iostream>

ForwardAmbient::ForwardAmbient()
	: Shader()
{
	this->load_shader();
}

ForwardAmbient &ForwardAmbient::get_instance()
{
	static ForwardAmbient instance;
	return instance;
}

void ForwardAmbient::load_shader()
{
	this->load("shaders/forwardAmbient.vert",
		   "shaders/forwardAmbient.frag");
	this->add_uniform("ambient_intensity");
	this->add_uniform("MVP");
}

void ForwardAmbient::update_uniforms(Transform *transform,
				     const Material &material)
{
	BaseCamera *camera = static_cast<BaseCamera *>(
		SharedGlobals::get_instance().main_camera);

	Matrix4f projected_matrix =
		Matrix4f::flip_matrix(camera->get_view_projection() *
				      transform->get_transformation());

	static_cast<Texture *>(material.get_property("diffuse"))->bind();

	this->set_uniform("MVP", projected_matrix);
	this->set_uniform("ambient_intensity",
			  SharedGlobals::get_instance().active_ambient_light);
}
