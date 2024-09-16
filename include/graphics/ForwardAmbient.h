/***************************************************************************
 * @file ForwardAmbient.h
 *
 * @brief Declares the ForwardAmbient class for the ambient lighting as part of
 * the forward rendering pipeline.
 *
 * This file contains the declaration of the ForwardAmbient class, which extends
 * the Shader class to provide ambient lighting as part of the forward rendering
 * pipeline. It includes methods for loading shaders and updating uniforms specific 
 * to basic shading.
 *
 ***************************************************************************/

#pragma once

#include <math/Matrix4f.h>
#include <math/Transform.h>

#include <components/BaseCamera.h>

#include <graphics/Shader.h>
#include <graphics/Material.h>

/***************************************************************************
 * @class ForwardAmbient
 *
 * @brief Represents the ambient lighting of the forward rendering pipeline
 *
 * The ForwardAmbient class provides functionality for loading and using shaders.
 * It is intended for ambient lighting as part of the forward rendering pipeline.
 *
 ***************************************************************************/
class ForwardAmbient : public Shader {
	ForwardAmbient();

    public:
	ForwardAmbient(const ForwardAmbient &) = delete;
	ForwardAmbient &operator=(const ForwardAmbient &) = delete;

	/***************************************************************************
	 * @brief Gets the singleton instance of the ForwardAmbient.
	 *
	 * @return The singleton instance of the ForwardAmbient.
	 ***************************************************************************/
	static ForwardAmbient &get_instance();

	/***************************************************************************
	 * @brief Loads the vertex and fragment shaders.
	 ***************************************************************************/
	void load_shader();

	/***************************************************************************
	 * @brief Updates the shader's uniform variables.
	 *
	 * @param transform The transformation matrix to use.
	 * @param material The material properties to use.
	 ***************************************************************************/
	void update_uniforms(Transform *transform,
			     const Material &material) override;
};
