#include <graphics/PhongShader.h>

#include <math/Matrix4f.h>
#include <math/Vector3f.h>

#include <core/Camera.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>
#include <graphics/BaseLight.h>
#include <graphics/PointLight.h>
#include <graphics/DirectionalLight.h>

#include <vector>
#include <iostream>
#include <exception>

/***************************************************************************
 * @brief Default constructor for PhongShader.
 *
 * Initializes a PhongShader object by calling the base class constructor.
 ***************************************************************************/
PhongShader::PhongShader()
	: Shader()
{
	this->load_shader();
}

/***************************************************************************
 * @brief Gets the singleton instance of PhongShader.
 *
 * @return A reference to the singleton PhongShader instance.
 ***************************************************************************/
PhongShader &PhongShader::get_instance()
{
	static PhongShader instance;
	return instance;
}

/***************************************************************************
 * @brief Loads vertex and fragment shaders.
 *
 * Loads the vertex and fragment shaders from the specified file paths and 
 * adds the required uniform variables for Phong shading.
 ***************************************************************************/
void PhongShader::load_shader()
{
	this->load("shaders/phongShader.vert", "shaders/phongShader.frag");
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

	for (int i = 0; i < MAX_POINT_LIGHTS; i++) {
		const std::string prefix = "point_lights[" + std::to_string(i);
		add_uniform(prefix + "].base_light.color");
		add_uniform(prefix + "].base_light.intensity");
		add_uniform(prefix + "].attenuation.constant");
		add_uniform(prefix + "].attenuation.linear");
		add_uniform(prefix + "].attenuation.exponent");
		add_uniform(prefix + "].position");
		add_uniform(prefix + "].range");
	}

	for (int i = 0; i < MAX_SPOT_LIGHTS; i++) {
		const std::string prefix = "spot_lights[" + std::to_string(i);
		add_uniform(prefix + "].point_light.base_light.color");
		add_uniform(prefix + "].point_light.base_light.intensity");
		add_uniform(prefix + "].point_light.attenuation.constant");
		add_uniform(prefix + "].point_light.attenuation.linear");
		add_uniform(prefix + "].point_light.attenuation.exponent");
		add_uniform(prefix + "].point_light.position");
		add_uniform(prefix + "].point_light.range");
		add_uniform(prefix + "].direction");
		add_uniform(prefix + "].cutoff");
	}
}

/***************************************************************************
 * @brief Updates the shader uniforms with transform and material data.
 *
 * Sets the uniform values for the shader based on the provided transform 
 * and material data. Includes setting up lighting and camera information.
 *
 * @param transform The transform object containing transformation matrices.
 * @param material The material object containing material properties.
 ***************************************************************************/
void PhongShader::update_uniforms(const Transform &transform,
				  const Material &material)
{
	static Camera &camera = Camera::get_instance();

	Vector3f camera_position = camera.get_position();

	Matrix4f world_matrix = transform.get_transformation();
	Matrix4f projected_matrix = Matrix4f::flip_matrix(
		camera.get_view_projection() * world_matrix);
	world_matrix = Matrix4f::flip_matrix(world_matrix);

	material.get_texture().bind();

	this->set_uniform("transform_projected", projected_matrix);
	this->set_uniform("transform", world_matrix);

	this->set_uniform("ambient_light", ambient_light);
	this->set_uniform("directional_light", directional_light);

	for (int i = 0; i < point_lights.size(); i++) {
		const std::string uniform =
			"point_lights[" + std::to_string(i) + "]";
		this->set_uniform(uniform, point_lights[i]);
	}
	for (int i = 0; i < spot_lights.size(); i++) {
		const std::string uniform =
			"spot_lights[" + std::to_string(i) + "]";
		this->set_uniform(uniform, spot_lights[i]);
	}

	this->set_uniform("base_color", material.get_color());
	this->set_uniform("specular", material.get_specular());
	this->set_uniform("eyePos", camera_position);
}

/***************************************************************************
 * @brief Gets the ambient light for the shader.
 *
 * @return A reference to the ambient light vector.
 ***************************************************************************/
Vector3f &PhongShader::get_ambient_light() noexcept
{
	return ambient_light;
}

/***************************************************************************
 * @brief Sets the ambient light for the shader.
 *
 * Updates the ambient light vector used in the shader.
 *
 * @param ambient_light The ambient light vector to set.
 ***************************************************************************/
void PhongShader::set_ambient_light(const Vector3f &ambient_light) noexcept
{
	this->ambient_light = Vector3f(ambient_light);
}

/***************************************************************************
 * @brief Gets the directional light for the shader.
 *
 * @return A reference to the directional light.
 ***************************************************************************/
DirectionalLight &PhongShader::get_directional_light() noexcept
{
	return directional_light;
}

/***************************************************************************
 * @brief Sets the directional light for the shader.
 *
 * Updates the directional light data used in the shader.
 *
 * @param directional_light The directional light to set.
 ***************************************************************************/
void PhongShader::set_directional_light(
	const DirectionalLight &directional_light) noexcept
{
	this->directional_light.base_light = directional_light.base_light;
	this->directional_light.direction =
		directional_light.direction.normalize();
}

/***************************************************************************
 * @brief Sets the point lights for the shader.
 *
 * Updates the list of point lights used in the shader. Throws an exception
 * if the number of point lights exceeds the maximum allowed.
 *
 * @param point_lights The vector of point lights to set.
 * @throws std::invalid_argument If the number of point lights exceeds the 
 *         maximum allowed.
 ***************************************************************************/
void PhongShader::set_point_lights(const std::vector<PointLight> &point_lights)
{
	if (point_lights.size() > MAX_POINT_LIGHTS) {
		std::cerr << "Error: Too Many Point Lights:\tCurrent: "
			  << point_lights.size()
			  << "\tMax: " << MAX_POINT_LIGHTS << '\n';
		throw std::invalid_argument("Too many Point Lights");
	}

	this->point_lights = point_lights;
}

/***************************************************************************
 * @brief Sets the spot lights for the shader.
 *
 * Updates the list of spot lights used in the shader. Throws an exception
 * if the number of spot lights exceeds the maximum allowed.
 *
 * @param spot_lights The vector of spot lights to set.
 * @throws std::invalid_argument If the number of spot lights exceeds the 
 *         maximum allowed.
 ***************************************************************************/
void PhongShader::set_spot_lights(const std::vector<SpotLight> &spot_lights)
{
	if (spot_lights.size() > MAX_SPOT_LIGHTS) {
		std::cerr << "Error: Too Many Spot Lights:\tCurrent: "
			  << spot_lights.size() << "\tMax: " << MAX_SPOT_LIGHTS
			  << '\n';
		throw std::invalid_argument("Too many Spot Lights");
	}

	this->spot_lights = spot_lights;
}

/***************************************************************************
 * @brief Sets uniform values for a base light.
 *
 * Updates the shader uniform for a base light, including color and intensity.
 *
 * @param uniform The base name of the uniform.
 * @param base_light The base light data to set.
 ***************************************************************************/
void PhongShader::set_uniform(const std::string &uniform,
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
void PhongShader::set_uniform(const std::string &uniform,
			      const DirectionalLight &directional_light) noexcept
{
	set_uniform(uniform + ".base_light", directional_light.base_light);
	set_uniform(uniform + ".direction", directional_light.direction);
}

/***************************************************************************
 * @brief Sets uniform values for specular lighting.
 *
 * Updates the shader uniform for specular lighting, including intensity and 
 * exponent.
 *
 * @param uniform The base name of the uniform.
 * @param specular The specular lighting data to set.
 ***************************************************************************/
void PhongShader::set_uniform(const std::string &uniform,
			      const Specular &specular) noexcept
{
	set_uniform(uniform + ".intensity", specular.intensity);
	set_uniform(uniform + ".exponent", specular.exponent);
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
void PhongShader::set_uniform(const std::string &uniform,
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
void PhongShader::set_uniform(const std::string &uniform,
			      const SpotLight &spot_light) noexcept
{
	set_uniform(uniform + ".point_light", spot_light.point_light);
	set_uniform(uniform + ".direction", spot_light.direction);
	set_uniform(uniform + ".cutoff", spot_light.cutoff);
}
