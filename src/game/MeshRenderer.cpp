#include <game/MeshRenderer.h>

#include <math/Transform.h>

#include <core/Camera.h>

#include <graphics/Mesh.h>
#include <graphics/Shader.h>
#include <graphics/Material.h>

#include <game/GameComponent.h>

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