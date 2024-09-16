#include <graphics/ForwardPoint.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>

#include <components/LightSources.h>
#include <components/BaseLight.h>
#include <components/PointLight.h>

#include <iostream>

/***************************************************************************
 * @brief Constructs a ForwardPoint instance.
 *
 * This constructor initializes a ForwardPoint object by calling the base 
 * Shader constructor.
 ***************************************************************************/
ForwardPoint::ForwardPoint()
	: Shader()
{
	this->load_shader();
}

/***************************************************************************
 * @brief Retrieves the singleton instance of ForwardPoint.
 *
 * @return The singleton instance of ForwardPoint.
 ***************************************************************************/
ForwardPoint &ForwardPoint::get_instance()
{
	static ForwardPoint instance;
	return instance;
}

/***************************************************************************
 * @brief Loads shader files and initializes uniforms.
 *
 * Loads the vertex and fragment shader files, and adds the necessary 
 * uniforms "model" and "MVP" to the shader.
 ***************************************************************************/
void ForwardPoint::load_shader()
{
	this->load("shaders/forwardPoint.vert", "shaders/forwardPoint.frag");

	this->add_uniform("model");
	this->add_uniform("MVP");

	this->add_uniform("point_light.base_light.color");
	this->add_uniform("point_light.base_light.intensity");
	this->add_uniform("point_light.attenuation.constant");
	this->add_uniform("point_light.attenuation.linear");
	this->add_uniform("point_light.attenuation.exponent");
	this->add_uniform("point_light.position");
	this->add_uniform("point_light.range");

	this->add_uniform("specular.intensity");
	this->add_uniform("specular.exponent");
	this->add_uniform("eyePos");
}

/***************************************************************************
 * @brief Updates shader uniforms with the given model and material.
 *
 * Sets the shader uniforms for "model" and "MVP" using the provided
 * model and material. Binds the texture from the material.
 *
 * @param model The model to be used for the shader's "model" uniform.
 * @param material The material to be used for the shader's "MVP" uniform and texture.
 ***************************************************************************/
void ForwardPoint::update_uniforms(const Transform &transform,
				   const Material &material)
{
	static Camera &camera = Camera::get_instance();

	Vector3f camera_position = camera.get_position();

	Matrix4f world_matrix = transform.get_transformation();
	Matrix4f projected_matrix = Matrix4f::flip_matrix(
		camera.get_view_projection() * world_matrix);
	world_matrix = Matrix4f::flip_matrix(world_matrix);

	material.get_texture().bind();

	this->set_uniform("model", world_matrix);
	this->set_uniform("MVP", projected_matrix);

	this->set_uniform("specular", material.get_specular());
	this->set_uniform("eyePos", camera_position);

	this->set_uniform(
		"point_light",
		*static_cast<PointLight *>(
			LightSources::get_instance().active_point_light));
}

/***************************************************************************
 * @brief Sets uniform values for a base light.
 *
 * Updates the shader uniform for a base light, including color and intensity.
 *
 * @param uniform The base name of the uniform.
 * @param base_light The base light data to set.
 ***************************************************************************/
void ForwardPoint::set_uniform(const std::string &uniform,
			       const BaseLight &base_light) noexcept
{
	this->set_uniform(uniform + ".color", base_light.color);
	this->set_uniform(uniform + ".intensity", base_light.intensity);
}

/***************************************************************************
 * @brief Sets uniform values for a point light.
 *
 * Updates the shader uniform for a point light, including base light data, 
 * attenuation parameters, position, and range.
 *
 * @param uniform The base name of the uniform.
 * @param point_light The point light data to set.
 ***************************************************************************/
void ForwardPoint::set_uniform(const std::string &uniform,
			       const PointLight &point_light) noexcept
{
	set_uniform(uniform + ".base_light",
		    BaseLight{ point_light.color, point_light.intensity });
	set_uniform(uniform + ".attenuation.constant",
		    point_light.attenuation.constant);
	set_uniform(uniform + ".attenuation.linear",
		    point_light.attenuation.linear);
	set_uniform(uniform + ".attenuation.exponent",
		    point_light.attenuation.exponent);
	set_uniform(uniform + ".position", point_light.position);
	set_uniform(uniform + ".range", point_light.range);
}
