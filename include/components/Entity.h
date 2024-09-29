#pragma once

#include <core/Input.h>
#include <core/Timer.h>

#include <graphics/Mesh.h>
#include <graphics/Shader.h>
#include <graphics/Texture.h>
#include <graphics/Specular.h>

#include <components/SharedGlobals.h>
#include <components/MeshRenderer.h>
#include <components/GameObject.h>
#include <components/GameComponent.h>

#include <string>
#include <cmath>
#include <algorithm>

#define SPAWN_HEIGHT 7.5f

class Entity : public GameObject {
	btRigidBody *rigid_body = nullptr;

    public:
	const btScalar move_impulse_factor = 2e3;
	const btScalar rotate_impulse_factor = 4e2;
	const btScalar jump_units = 1.5e3;
	const btScalar max_move_velocity = 8.5f;
	const btScalar max_jump_velocity = 6.0f;
	bool on_ground = true;
	bool player;

	Entity(const std::string &mesh_path, const std::string &diffuse_path,
	       bool player = false)
		: player(player)
	{
		this->physics_type = 20; // Physics for person entities
		transform.set_translation(Vector3f(0.0f, 0.0f, SPAWN_HEIGHT));

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

			btTransform transform;
			transform.setIdentity();
			transform.setOrigin(
				btVector3(0.0f, 0.0f, SPAWN_HEIGHT));
			rigid_body->setWorldTransform(transform);

			SharedGlobals::get_instance().rigid_bodies.push_back(
				rigid_body);

			rigid_body->setDamping(0.1f, 0.4f);
		}
	}

	void update(float delta) override
	{
		if (rigid_body) {
			btVector3 velocity = rigid_body->getLinearVelocity();

			btScalar x = velocity.getX();
			btScalar y = velocity.getY();
			btScalar z = velocity.getZ();

			btScalar xy_length = std::sqrt(x * x + y * y) + 1e-9;

			if (xy_length > max_move_velocity) {
				btScalar scale = max_move_velocity / xy_length;

				velocity.setX(x * scale);
				velocity.setY(y * scale);
				velocity.setZ(std::min(z, max_jump_velocity));

				rigid_body->setLinearVelocity(velocity);
			}
			btTransform world_transform =
				rigid_body->getWorldTransform();

			btVector3 position = world_transform.getOrigin();
			x = position.getX();
			y = position.getY();
			z = position.getZ();
			transform.set_translation(Vector3f(x, y, z));

			btQuaternion quaternion = world_transform.getRotation();
			transform.set_rotation(
				{ quaternion.getX(), quaternion.getY(),
				  quaternion.getZ(), quaternion.getW() });
		}

		GameObject::update();
	}

	void move(const Vector3f &direction, float amount) noexcept
	{
		if (rigid_body) {
			rigid_body->activate();
			btVector3 impulse(direction.getX() * amount,
					  direction.getY() * amount,
					  direction.getZ() * amount);
			rigid_body->applyCentralImpulse(impulse);
		}
	}

	void rotate(const Vector3f &direction, float amount) noexcept
	{
		if (rigid_body) {
			rigid_body->activate();
			btVector3 impulse(direction.getX() * amount,
					  direction.getY() * amount,
					  direction.getZ() * amount);
			rigid_body->applyTorqueImpulse(impulse);
		}
	}

	void input(float delta) override
	{
		static Input &input_handler = Input::get_instance();
		static Timer &timer = Timer::get_instance();
		if (player) {
			if (input_handler.is_key_pressed(GLFW_KEY_W)) {
				move(transform.get_rotation().get_forward(),
				     move_impulse_factor * delta);
			}
			if (input_handler.is_key_pressed(GLFW_KEY_A)) {
				move(transform.get_rotation().get_left(),
				     move_impulse_factor * delta);
			}
			if (input_handler.is_key_pressed(GLFW_KEY_S)) {
				move(transform.get_rotation().get_backward(),
				     move_impulse_factor * delta);
			}
			if (input_handler.is_key_pressed(GLFW_KEY_D)) {
				move(transform.get_rotation().get_right(),
				     move_impulse_factor * delta);
			}
			if (input_handler.is_key_pressed(GLFW_KEY_E)) {
				rotate(Vector3f::z_axis,
				       rotate_impulse_factor * delta);
			}
			if (input_handler.is_key_pressed(GLFW_KEY_Q)) {
				rotate(Vector3f::z_axis,
				       -rotate_impulse_factor * delta);
			}

			static float jump_cd = 0.0;
			if (jump_cd > 0) {
				jump_cd -= timer.get_delta_time();
			} else {
				if (on_ground && input_handler.is_key_pressed(
							 GLFW_KEY_SPACE)) {
					move(transform.get_rotation().get_up(),
					     jump_units);
					jump_cd = 1.5f;
				}
			}
		}
		on_ground = false;
		GameObject::input(delta);
	}

	void handle_collision(GameObject *obj) override
	{
		if (obj->physics_type == 10) {
			on_ground = true;
		}
	}
};

#undef SPAWN_HEIGHT