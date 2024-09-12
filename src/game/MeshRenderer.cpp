#include <game/MeshRenderer.h>

#include <math/Transform.h>

#include <core/Camera.h>

#include <graphics/Mesh.h>
#include <graphics/Shader.h>
#include <graphics/Material.h>

#include <game/GameComponent.h>

/***************************************************************************
 * @brief Constructs a MeshRenderer with the specified mesh and material.
 *
 * @param mesh The mesh to be rendered.
 * @param material The material to be used for rendering.
 ***************************************************************************/
MeshRenderer::MeshRenderer(const Mesh &mesh, const Material &material)
	: mesh(mesh)
	, material(material)
{
}

/***************************************************************************
 * @brief Processes input for the MeshRenderer.
 *
 * This function is currently not implemented.
 *
 * @param transform The transform associated with this MeshRenderer.
 ***************************************************************************/
void MeshRenderer::input(const Transform &transform)
{
}

/***************************************************************************
 * @brief Updates the MeshRenderer.
 *
 * This function is currently not implemented.
 *
 * @param transform The transform associated with this MeshRenderer.
 ***************************************************************************/
void MeshRenderer::update(const Transform &transform)
{
}

/***************************************************************************
 * @brief Renders the mesh using the provided shader and transform.
 *
 * Uses the shader program, updates the shader's uniforms with the provided 
 * transform and material, and draws the mesh.
 *
 * @param transform The transform to apply to the mesh.
 * @param shader The shader to use for rendering the mesh.
 ***************************************************************************/
void MeshRenderer::render(const Transform &transform, Shader &shader)
{
	shader.use_program();
	shader.update_uniforms(transform, material);
	mesh.draw();
}
