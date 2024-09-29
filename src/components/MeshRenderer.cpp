#include <components/MeshRenderer.h>

#include <math/Transform.h>

#include <components/BaseCamera.h>

#include <graphics/Mesh.h>
#include <graphics/Shader.h>
#include <graphics/Material.h>

#include <components/SharedGlobals.h>
#include <components/GameComponent.h>

MeshRenderer::MeshRenderer(const Mesh &mesh, const Material &material)
	: mesh(mesh)
	, material(material) {};

void MeshRenderer::render(Shader &shader)
{
	shader.use_program();
	shader.update_uniforms(get_parent_transform(), material);
	mesh.draw();
}

Material &MeshRenderer::get_material()
{
	return material;
}