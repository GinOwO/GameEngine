#include <game/MeshRenderer.h>

#include <core/Camera.h>

#include <game/GameComponent.h>

#include <graphics/Shader.h>
#include <graphics/Mesh.h>
#include <graphics/Material.h>

#include <math/Transform.h>

MeshRenderer::MeshRenderer(const Mesh &mesh, const Material &material)
	: mesh(mesh)
	, material(material)
{
}

void MeshRenderer::input(const Transform &transform)
{
}

void MeshRenderer::update(const Transform &transform)
{
}

void MeshRenderer::render(const Transform &transform, Shader &shader)
{
	shader.use_program();
	Matrix4f projection_matrix = Matrix4f::flip_matrix(
		transform.get_projected_camera(Camera::get_instance()));

	Matrix4f transformation_matrix =
		Matrix4f::flip_matrix(transform.get_transformation());

	shader.update_uniforms(transformation_matrix, projection_matrix,
			       material);

	mesh.draw();
}