#pragma once

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

class Person : public GameObject {
	float move_speed = 5.0f;
	btRigidBody *rigid_body = nullptr;

    public:
	bool on_ground = true, player = false;

	Person(const std::string &mesh_path, const std::string &diffuse_path)
	{
		this->physics_type = 20; // Physics for person entities
		Mesh mesh = Mesh::load_mesh(mesh_path,
					    Mesh::MeshPhysicsType::ENTITY);
		Material material;

		material.add_property("diffuse",
				      Texture::load_texture(diffuse_path));

		material.add_property(
			"specular", std::shared_ptr<void>(new Specular{ 0, 0 },
							  Specular::deleter));

		this->add_component(new MeshRenderer(mesh, material));

		if (SharedGlobals::get_instance().current_rigid_body) {
			this->rigid_body =
				SharedGlobals::get_instance().current_rigid_body;
			rigid_body->setUserPointer(this);

			SharedGlobals::get_instance().rigid_bodies.push_back(
				rigid_body);
		}
	}

	void update(float delta) override
	{
		if (!on_ground) {
			move(transform.get_rotation().get_up(),
			     -SharedGlobals::get_instance().GRAVITY * delta);
		}

		GameObject::update();
	}

	void move(const Vector3f &direction, float amount) noexcept
	{
		transform.set_translation(transform.get_translation() +
					  (direction * amount));

		btTransform new_transform;
		new_transform.setIdentity();
		new_transform.setOrigin(
			btVector3(transform.get_translation().getX(),
				  transform.get_translation().getY(),
				  transform.get_translation().getZ()));

		auto rigid_body = dynamic_cast<btRigidBody *>(this->rigid_body);
		if (rigid_body) {
			rigid_body->setWorldTransform(new_transform);
		}
	}

	void input(float delta) override
	{
		static Input &input_handler = Input::get_instance();
		if (on_ground && player) {
			if (input_handler.is_key_pressed(GLFW_KEY_UP)) {
				move(transform.get_rotation().get_forward(),
				     move_speed * delta);
			}
			if (input_handler.is_key_pressed(GLFW_KEY_DOWN)) {
				move(transform.get_rotation().get_backward(),
				     move_speed * delta);
			}
			if (input_handler.is_key_pressed(GLFW_KEY_LEFT)) {
				move(transform.get_rotation().get_left(),
				     move_speed * delta);
			}
			if (input_handler.is_key_pressed(GLFW_KEY_RIGHT)) {
				move(transform.get_rotation().get_right(),
				     move_speed * delta);
			}
		}
		GameObject::input(delta);
	}
};