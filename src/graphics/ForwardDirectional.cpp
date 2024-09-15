#include <graphics/ForwardDirectional.h>

#include <graphics/BaseLight.h>
#include <graphics/DirectionalLight.h>
#include <graphics/Shader.h>
#include <graphics/Material.h>

#include <iostream>

/***************************************************************************
 * @brief Constructs a ForwardDirectional instance.
 *
 * This constructor initializes a ForwardDirectional object by calling the base 
 * Shader constructor.
 ***************************************************************************/
ForwardDirectional::ForwardDirectional()
	: Shader()
{
	this->load_shader();
}

/***************************************************************************
 * @brief Retrieves the singleton instance of ForwardDirectional.
 *
 * @return The singleton instance of ForwardDirectional.
 ***************************************************************************/
ForwardDirectional &ForwardDirectional::get_instance()
{
	static ForwardDirectional instance;
	return instance;
}

/***************************************************************************
 * @brief Loads shader files and initializes uniforms.
 *
 * Loads the vertex and fragment shader files, and adds the necessary 
 * uniforms "model" and "MVP" to the shader.
 ***************************************************************************/
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

/***************************************************************************
 * @brief Updates shader uniforms with the given model and material.
 *
 * Sets the shader uniforms for "model" and "MVP" using the provided
 * model and material. Binds the texture from the material.
 *
 * @param model The model to be used for the shader's "model" uniform.
 * @param material The material to be used for the shader's "MVP" uniform and texture.
 ***************************************************************************/
void ForwardDirectional::update_uniforms(const Transform &transform,
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

	this->set_uniform("directional_light", directional_light);
}

/***************************************************************************
 * @brief Sets uniform values for a base light.
 *
 * Updates the shader uniform for a base light, including color and intensity.
 *
 * @param uniform The base name of the uniform.
 * @param base_light The base light data to set.
 ***************************************************************************/
void ForwardDirectional::set_uniform(const std::string &uniform,
				     const BaseLight &base_light) noexcept
{
	this->set_uniform(uniform + ".color", base_light.color);
	this->set_uniform(uniform + ".intensity", base_light.intensity);
}

/***************************************************************************
 * @brief Sets uniform values for a directional light.
 *
 * Updates the shader uniform for a directional light, including base light 
 * data and direction.
 *
 * @param uniform The base name of the uniform.
 * @param directional_light The directional light data to set.
 ***************************************************************************/
void ForwardDirectional::set_uniform(
	const std::string &uniform,
	const DirectionalLight &directional_light) noexcept
{
	set_uniform(uniform + ".base_light", directional_light.base_light);
	set_uniform(uniform + ".direction", directional_light.direction);
}