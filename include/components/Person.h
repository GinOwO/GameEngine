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

class Person : public GameObject {
    public:
	Person(const std::string &mesh_path, const std::string &diffuse_path)
	{
		Mesh mesh = Mesh::load_mesh(mesh_path);
		Material material;

		material.add_property("diffuse",
				      Texture::load_texture(diffuse_path));

		material.add_property(
			"specular", std::shared_ptr<void>(new Specular{ 0, 0 },
							  Specular::deleter));

		this->add_component(new MeshRenderer(mesh, material));
	}
};