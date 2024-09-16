#include <graphics/ForwardAmbient.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>

#include <components/LightSources.h>

#include <iostream>

/***************************************************************************
 * @brief Constructs a ForwardAmbient instance.
 *
 * This constructor initializes a ForwardAmbient object by calling the base 
 * Shader constructor.
 ***************************************************************************/
ForwardAmbient::ForwardAmbient()
	: Shader()
{
	this->load_shader();
}

/***************************************************************************
 * @brief Retrieves the singleton instance of ForwardAmbient.
 *
 * @return The singleton instance of ForwardAmbient.
 ***************************************************************************/
ForwardAmbient &ForwardAmbient::get_instance()
{
	static ForwardAmbient instance;
	return instance;
}

/***************************************************************************
 * @brief Loads shader files and initializes uniforms.
 *
 * Loads the vertex and fragment shader files, and adds the necessary 
 * uniforms "transform" and "MVP" to the shader.
 ***************************************************************************/
void ForwardAmbient::load_shader()
{
	this->load("shaders/forwardAmbient.vert",
		   "shaders/forwardAmbient.frag");
	this->add_uniform("ambient_intensity");
	this->add_uniform("MVP");
}

/***************************************************************************
 * @brief Updates shader uniforms with the given transform and material.
 *
 * Sets the shader uniforms for "transform" and "color" using the provided
 * transform and material. Binds the texture from the material.
 *
 * @param transform The transform to be used for the shader's "transform" uniform.
 * @param material The material to be used for the shader's "color" uniform and texture.
 ***************************************************************************/
void ForwardAmbient::update_uniforms(const Transform &transform,
				     const Material &material)
{
	static Camera &camera = Camera::get_instance();

	Matrix4f projected_matrix = Matrix4f::flip_matrix(
		camera.get_view_projection() * transform.get_transformation());

	material.get_texture().bind();

	this->set_uniform("MVP", projected_matrix);
	this->set_uniform("ambient_intensity",
			  LightSources::get_instance().active_ambient_light);
}
