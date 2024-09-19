/***************************************************************************
 * @file MeshRenderer.h
 *
 * @brief Declares the MeshRenderer class for rendering meshes with materials.
 *
 * This file contains the declaration of the MeshRenderer class, which
 * is a component responsible for rendering a mesh with a specified material.
 * It inherits from GameComponent and implements the input, update, and
 * render methods.
 *
 ***************************************************************************/

#pragma once

#include <math/Transform.h>

#include <graphics/Mesh.h>
#include <graphics/Shader.h>
#include <graphics/Material.h>

#include <components/GameComponent.h>

/***************************************************************************
 * @class MeshRenderer
 *
 * @brief Renders a mesh using a material and shader.
 *
 * The MeshRenderer class is a GameComponent that renders a Mesh using a
 * specified Material and Shader. It overrides the input, update, and render
 * methods from the GameComponent base class to perform mesh rendering
 * operations.
 *
 ***************************************************************************/
class MeshRenderer : public GameComponent {
    private:
	/***************************************************************************
	 * @brief The Mesh to be rendered.
	 ***************************************************************************/
	Mesh mesh;

	/***************************************************************************
	 * @brief The Material used for rendering the Mesh.
	 ***************************************************************************/
	Material material;

    public:
	/***************************************************************************
	 * @brief Deleted default constructor.
	 *
	 * The default constructor is deleted to prevent the creation of a
	 * MeshRenderer without specifying a Mesh and Material.
	 ***************************************************************************/
	MeshRenderer() = delete;

	/***************************************************************************
	 * @brief Constructs a MeshRenderer with specified Mesh and Material.
	 *
	 * @param mesh The Mesh to be rendered.
	 * @param material The Material used for rendering the Mesh.
	 ***************************************************************************/
	MeshRenderer(const Mesh &mesh, const Material &material);

	/***************************************************************************
	 * @brief Handles input for the MeshRenderer.
	 *
	 * @param transform The Transform object representing the component's
	 *		  position and orientation.
	 ***************************************************************************/
	void input() override;

	/***************************************************************************
	 * @brief Updates the MeshRenderer.
	 *
	 * @param transform The Transform object representing the component's
	 *		  position and orientation.
	 ***************************************************************************/
	void update() override;

	/***************************************************************************
	 * @brief Renders the Mesh using the provided Shader.
	 *
	 * @param transform The Transform object representing the component's
	 *		  position and orientation.
	 * @param shader The Shader used for rendering the Mesh.
	 ***************************************************************************/
	void render(Shader &shader) override;
};
