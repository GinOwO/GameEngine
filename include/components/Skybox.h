#pragma once

#include <math/Vector3f.h>

#include <core/Input.h>

#include <graphics/Mesh.h>
#include <graphics/Shader.h>
#include <graphics/Texture.h>
#include <graphics/Specular.h>

#include <components/SharedGlobals.h>
#include <components/MeshRenderer.h>
#include <components/GameObject.h>
#include <components/GameComponent.h>

#include <string>

class Skybox : public GameObject {
	Vector3f rotate_sens;

    public:
	Skybox(const std::string &mesh_path, const std::string &texture_path,
	       const Vector3f &rotate_sens = { 1, 1, 1 })
		: rotate_sens(rotate_sens)
	{
		Mesh skbox = Mesh::load_mesh(mesh_path);
		Material skmaterial;

		skmaterial.add_property("diffuse",
					Texture::load_texture(texture_path));

		skmaterial.add_property(
			"specular", std::shared_ptr<void>(new Specular{ 0, 0 },
							  Specular::deleter));

		this->add_component(new MeshRenderer(skbox, skmaterial));
	}

	void render(Shader &shader) override
	{
		Vector3f previous_ambient_light =
			SharedGlobals::get_instance().active_ambient_light;

		float intensity = 0;
		BaseLight *tmp = static_cast<BaseLight *>(
			SharedGlobals::get_instance().active_light);

		if (tmp != nullptr) {
			intensity = tmp->intensity;
		}

		SharedGlobals::get_instance().active_ambient_light = { 1, 1,
								       1 };

		GameObject::render(shader);

		if (tmp != nullptr) {
			tmp->intensity = intensity;
		}

		SharedGlobals::get_instance().active_ambient_light =
			previous_ambient_light;
	}

	void update(float delta) override
	{
		transform
			.rotate({ 1, 0, 0 },
				to_radians(delta * rotate_sens.getX()))
			.rotate({ 0, 1, 0 },
				to_radians(delta * rotate_sens.getY()))
			.rotate({ 0, 0, 1 },
				to_radians(delta * rotate_sens.getZ()));

		Transform *camera_transform =
			static_cast<Camera *>(
				SharedGlobals::get_instance().main_camera)
				->get_parent_transform();

		transform.set_translation(camera_transform->get_translation());
		GameObject::update(delta);
	}
};