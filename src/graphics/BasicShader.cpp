#include <graphics/BasicShader.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>

#include <components/SharedGlobals.h>

#include <iostream>

/***************************************************************************
 * @brief Constructs a BasicShader instance.
 *
 * This constructor initializes a BasicShader object by calling the base 
 * Shader constructor.
 ***************************************************************************/
BasicShader::BasicShader()
	: Shader()
{
	this->load_shader();
}

/***************************************************************************
 * @brief Retrieves the singleton instance of BasicShader.
 *
 * @return The singleton instance of BasicShader.
 ***************************************************************************/
BasicShader &BasicShader::get_instance()
{
	static BasicShader instance;
	return instance;
}

/***************************************************************************
 * @brief Loads shader files and initializes uniforms.
 *
 * Loads the vertex and fragment shader files, and adds the necessary 
 * uniforms "transform" and "color" to the shader.
 ***************************************************************************/
void BasicShader::load_shader()
{
	this->load("shaders/vertShader.vert", "shaders/fragShader.frag");
	this->add_uniform("transform");
	this->add_uniform("color");
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
void BasicShader::update_uniforms(Transform *transform,
				  const Material &material)
{
	BaseCamera *camera = static_cast<BaseCamera *>(
		SharedGlobals::get_instance().main_camera);

	Matrix4f projected_matrix =
		Matrix4f::flip_matrix(camera->get_view_projection() *
				      transform->get_transformation());

	material.get_texture().bind();

	this->set_uniform("transform", projected_matrix);
	this->set_uniform("color", material.get_color());
}
