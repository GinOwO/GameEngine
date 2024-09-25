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
		if (rigid_body) {
			btTransform world_transform =
				rigid_body->getWorldTransform();
			btVector3 position = world_transform.getOrigin();
			transform.set_translation(Vector3f(position.getX(),
							   position.getY(),
							   position.getZ()));
		}

		GameObject::update();
	}

	void move(const Vector3f &direction, float amount) noexcept
	{
		if (rigid_body) {
			btVector3 impulse(direction.getX() * amount * 10,
					  direction.getY() * amount * 10,
					  direction.getZ() * amount * 10);
			rigid_body->applyCentralImpulse(impulse);
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

	void handle_collision(GameObject *obj)
	{
		will_collide = true;
		// std::cout << "Colliding" << '\n';
	}
};