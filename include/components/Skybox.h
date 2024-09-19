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
	Vector3f light_prev;
	Vector3f rotate_sens;

    public:
	Skybox(const std::string &mesh_path, const std::string &texture_path,
	       const Vector3f &rotate_sens = { 1, 1, 1 })
		: rotate_sens(rotate_sens)
	{
		Mesh skbox = Mesh::load_mesh("assets/untitled.fbx");

		Texture *sktex = Texture::load_texture(
			"./assets/Skybox/fskybg/textures/background.jpg");

		Material skmaterial;

		skmaterial.add_property(
			"diffuse",
			std::shared_ptr<void>(sktex, Texture::deleter));

		skmaterial.add_property(
			"specular",
			std::shared_ptr<void>(
				new Specular{ 0, 0 }, [](void *ptr) {
					delete static_cast<Specular *>(ptr);
				}));

		this->add_component(new MeshRenderer(skbox, skmaterial));
	}

	void render(Shader &shader) override
	{
		Vector3f previous_ambient_light =
			SharedGlobals::get_instance().active_ambient_light;

		SharedGlobals::get_instance().active_ambient_light = { 1, 1,
								       1 };

		GameObject::render(shader);

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