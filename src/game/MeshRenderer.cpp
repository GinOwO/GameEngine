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

	shader.update_uniforms(transform, material);

	mesh.draw();
}