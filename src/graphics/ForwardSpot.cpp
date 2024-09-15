#include <graphics/ForwardSpot.h>

#include <graphics/BaseLight.h>
#include <graphics/SpotLight.h>
#include <graphics/Shader.h>
#include <graphics/Material.h>

#include <iostream>

/***************************************************************************
 * @brief Constructs a ForwardSpot instance.
 *
 * This constructor initializes a ForwardSpot object by calling the base 
 * Shader constructor.
 ***************************************************************************/
ForwardSpot::ForwardSpot()
	: Shader()
{
	this->load_shader();
}

/***************************************************************************
 * @brief Retrieves the singleton instance of ForwardSpot.
 *
 * @return The singleton instance of ForwardSpot.
 ***************************************************************************/
ForwardSpot &ForwardSpot::get_instance()
{
	static ForwardSpot instance;
	return instance;
}

/***************************************************************************
 * @brief Loads shader files and initializes uniforms.
 *
 * Loads the vertex and fragment shader files, and adds the necessary 
 * uniforms "model" and "MVP" to the shader.
 ***************************************************************************/
void ForwardSpot::load_shader()
{
	this->load("shaders/forwardSpot.vert", "shaders/forwardSpot.frag");

	this->add_uniform("model");
	this->add_uniform("MVP");

	this->add_uniform("spot_light.point_light.base_light.color");
	this->add_uniform("spot_light.point_light.base_light.intensity");
	this->add_uniform("spot_light.point_light.attenuation.constant");
	this->add_uniform("spot_light.point_light.attenuation.linear");
	this->add_uniform("spot_light.point_light.attenuation.exponent");
	this->add_uniform("spot_light.point_light.position");
	this->add_uniform("spot_light.point_light.range");
	this->add_uniform("spot_light.direction");
	this->add_uniform("spot_light.cutoff");

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
void ForwardSpot::update_uniforms(const Transform &transform,
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

	this->set_uniform("spot_light", spot_light);
}

/***************************************************************************
 * @brief Sets uniform values for a base light.
 *
 * Updates the shader uniform for a base light, including color and intensity.
 *
 * @param uniform The base name of the uniform.
 * @param base_light The base light data to set.
 ***************************************************************************/
void ForwardSpot::set_uniform(const std::string &uniform,
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
void ForwardSpot::set_uniform(const std::string &uniform,
			      const PointLight &point_light) noexcept
{
	set_uniform(uniform + ".base_light", point_light.base_light);
	set_uniform(uniform + ".attenuation.constant",
		    point_light.attenuation.constant);
	set_uniform(uniform + ".attenuation.linear",
		    point_light.attenuation.linear);
	set_uniform(uniform + ".attenuation.exponent",
		    point_light.attenuation.exponent);
	set_uniform(uniform + ".position", point_light.position);
	set_uniform(uniform + ".range", point_light.range);
}

/***************************************************************************
 * @brief Sets uniform values for a spot light.
 *
 * Updates the shader uniform for a spot light, including point light data, 
 * direction, and cutoff.
 *
 * @param uniform The base name of the uniform.
 * @param spot_light The spot light data to set.
 ***************************************************************************/
void ForwardSpot::set_uniform(const std::string &uniform,
			      const SpotLight &spot_light) noexcept
{
	set_uniform(uniform + ".point_light", spot_light.point_light);
	set_uniform(uniform + ".direction", spot_light.direction);
	set_uniform(uniform + ".cutoff", spot_light.cutoff);
}
