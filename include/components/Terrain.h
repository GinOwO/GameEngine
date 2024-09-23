#pragma once

#include <graphics/Mesh.h>
#include <graphics/Shader.h>
#include <graphics/Texture.h>
#include <graphics/Specular.h>

#include <components/SharedGlobals.h>
#include <components/MeshRenderer.h>
#include <components/GameObject.h>
#include <components/GameComponent.h>

#include <string>
#include <map>

class Terrain : public GameObject {
    public:
	Terrain(const std::string &mesh_path,
		const std::map<std::string, std::string> &texture_paths)
	{
		this->physics_type = 10; // Physics id for Terrains
		Mesh mesh = Mesh::load_mesh(mesh_path,
					    Mesh::MeshPhysicsType::NO_PHYSICS);
		Material material;

		for (auto &[tex_type, tex_path] : texture_paths) {
			material.add_property(tex_type,
					      Texture::load_texture(tex_path));
		}

		material.add_property(
			"specular", std::shared_ptr<void>(new Specular{ 0, 0 },
							  Specular::deleter));

		this->add_component(new MeshRenderer(mesh, material));
	}
};