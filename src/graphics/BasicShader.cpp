#include <graphics/BasicShader.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>

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
 *
 * @param vertex_path The path to the vertex shader file.
 * @param fragment_path The path to the fragment shader file.
 ***************************************************************************/
void BasicShader::load_shader(const std::string &vertex_path,
			      const std::string &fragment_path)
{
	this->load(vertex_path, fragment_path);
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
void BasicShader::update_uniforms(const Transform &transform,
				  const Material &material)
{
	static Camera &camera = Camera::get_instance();

	Matrix4f projected_matrix = Matrix4f::flip_matrix(
		camera.get_view_projection() * transform.get_transformation());

	material.get_texture().bind();

	this->set_uniform("transform", projected_matrix);
	this->set_uniform("color", material.get_color());
}
