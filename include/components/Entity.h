#pragma once

#include <core/Input.h>
#include <core/Timer.h>

#include <graphics/Mesh.h>
#include <graphics/Shader.h>
#include <graphics/Texture.h>
#include <graphics/Specular.h>

#include <core/SharedGlobals.h>
#include <components/MeshRenderer.h>
#include <components/GameObject.h>
#include <components/GameComponent.h>

#include <misc/SafeQueue.h>

#include <string>
#include <cmath>
#include <algorithm>

#define DEFAULT_ENTITY_SPAWN_POS { 0.0f, 5.0f, 10.0f }

class Entity : public GameObject {
    protected:
	btRigidBody *rigid_body = nullptr;
	btScalar move_impulse_factor = 2e3;
	btScalar rotate_impulse_factor = 4e2;
	btScalar jump_units = 1.5e3;
	btScalar max_move_velocity = 8.5f;
	btScalar max_jump_velocity = 6.0f;
	float hp = 1.0f, rec_dmg = 1.0f, max_hp = 1.0f;
	float jump_cd = 0.0;
	MeshRenderer *mesh = nullptr;

#ifdef MULTIPLAYER
	SafeQueue<std::pair<int32_t, std::vector<float> > > m_moves;
	int32_t m_action = -1;
	float m_delta = 0.0f;
#endif

    public:
	bool on_ground = true;
	bool player;

	struct EntityState {
		btVector3 position;
		btQuaternion orientation;
		btVector3 velocity;
		btVector3 angular_velocity;
		float hp;
	};

	Entity(const std::string &mesh_path, const std::string &diffuse_path,

	       const Vector3f &spawn_pos, bool player = false)
		: player(player)
	{
		this->physics_type = 20; // Physics for Entity entities
		transform.set_translation(Vector3f(spawn_pos));

		Mesh mesh = Mesh::load_mesh(mesh_path,
					    Mesh::MeshPhysicsType::ENTITY);
		Material material;

		material.add_property("diffuse",
				      Texture::load_texture(diffuse_path));

		material.add_property(
			"specular", std::shared_ptr<void>(new Specular{ 0, 0 },
							  Specular::deleter));

		this->add_component(this->mesh =
					    new MeshRenderer(mesh, material));

		if (SharedGlobals::get_instance().current_rigid_body) {
			this->rigid_body =
				SharedGlobals::get_instance().current_rigid_body;
			rigid_body->setUserPointer(this);

			btTransform transform;
			transform.setIdentity();
			transform.setOrigin(
				btVector3({ spawn_pos.getX(), spawn_pos.getY(),
					    spawn_pos.getZ() }));
			rigid_body->setWorldTransform(transform);

			SharedGlobals::get_instance().rigid_bodies.push_back(
				rigid_body);

			rigid_body->setDamping(0.1f, 0.4f);
		}

#ifdef MULTIPLAYER
		static SharedGlobals &globals = SharedGlobals::get_instance();
		if (player) {
			SharedGlobals::player_entity = this;
			globals.player_moves =
				static_cast<void *>(&this->m_moves);
		} else {
			SharedGlobals::enemy_entity = this;
			globals.enemy_moves =
				static_cast<void *>(&this->m_moves);
		}
#else
		if (player) {
			SharedGlobals::player_entity = this;
		} else {
			SharedGlobals::enemy_entity = this;
		}
#endif
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
		if (jump_cd > 0)
			jump_cd -= delta;

		GameObject::input(delta);
#ifdef MULTIPLAYER
		if (player) {
			if (m_action == 6)
				m_moves.push({ m_action, { m_delta } });
			// if (SharedGlobals::get_instance().get_tick() == 0)
			{
				EntityState state = get_entity_state();
				m_moves.push(
					{ 9, { state.position.x(),
					       state.position.y(),
					       state.position.z(),
					       state.orientation.x(),
					       state.orientation.y(),
					       state.orientation.z(),
					       state.orientation.w(),
					       state.velocity.x(),
					       state.velocity.y(),
					       state.velocity.z(),
					       state.angular_velocity.x(),
					       state.angular_velocity.y(),
					       state.angular_velocity.z() } });
			}
			m_action = -1;
			m_delta = 0;
		}
#endif
	}

	void handle_collision(GameObject *obj) override
	{
		if (obj->physics_type == 10) {
			on_ground = true;
		}
	}

	virtual float get_hp() const noexcept
	{
		return hp;
	}

	virtual void set_hp(float hp) noexcept
	{
		this->hp = hp;
	}

	virtual float get_max_hp() const noexcept
	{
		return max_hp;
	}

	virtual void set_max_hp(float max_hp) noexcept
	{
		this->max_hp = max_hp;
	}

	virtual void shoot()
	{
		Vector3f direction = transform.get_rotation().get_forward();

		Vector3f start = transform.get_translation();

		Vector3f end = start + direction * 100.0f;

		btCollisionWorld::ClosestRayResultCallback rayCallback(
			btVector3(start.getX(), start.getY(), start.getZ()),
			btVector3(end.getX(), end.getY(), end.getZ()));

		SharedGlobals::get_instance().dynamics_world->rayTest(
			btVector3(start.getX(), start.getY(), start.getZ()),
			btVector3(end.getX(), end.getY(), end.getZ()),
			rayCallback);

		if (rayCallback.hasHit()) {
			const btCollisionObject *hitObject =
				rayCallback.m_collisionObject;

			if (hitObject && hitObject->getUserPointer()) {
				if (static_cast<GameObject *>(
					    hitObject->getUserPointer())
					    ->physics_type == 20) {
					Entity *hitEntity = static_cast<Entity *>(
						hitObject->getUserPointer());
					hitEntity->get_hit();
				}
			}
		}
		m_action = 6;
		m_delta = 0;
	}

	virtual void get_hit()
	{
		hp -= rec_dmg * (hp > 0);
	}

	void move_forward(float delta)
	{
		move(transform.get_rotation().get_forward(),
		     move_impulse_factor * delta);
		m_action = 0;
		m_delta = delta;
	}

	void move_left(float delta)
	{
		move(transform.get_rotation().get_left(),
		     move_impulse_factor * delta);
		m_action = 1;
		m_delta = delta;
	}

	void move_backward(float delta)
	{
		move(transform.get_rotation().get_backward(),
		     move_impulse_factor * delta);
		m_action = 2;
		m_delta = delta;
	}

	void move_right(float delta)
	{
		move(transform.get_rotation().get_right(),
		     move_impulse_factor * delta);
		m_action = 3;
		m_delta = delta;
	}

	void rotate_left(float delta)
	{
		rotate(Vector3f::z_axis, rotate_impulse_factor * delta);
		m_action = 4;
		m_delta = delta;
	}

	void rotate_right(float delta)
	{
		rotate(Vector3f::z_axis, -rotate_impulse_factor * delta);
		m_action = 5;
		m_delta = delta;
	}

	void jump(float delta)
	{
		if (jump_cd <= 0) {
			if (on_ground)
				move(transform.get_rotation().get_up(),
				     jump_units);
			jump_cd = 1.5f;
		}
		m_action = 7;
		m_delta = delta;
	}

	EntityState get_entity_state()
	{
		EntityState state;

		btTransform transform = rigid_body->getWorldTransform();
		state.position = transform.getOrigin();
		state.orientation = transform.getRotation();

		state.velocity = rigid_body->getLinearVelocity();
		state.angular_velocity = rigid_body->getAngularVelocity();

		return state;
	}

	void apply_entity_state(const EntityState &state)
	{
		btTransform transform;
		transform.setOrigin(state.position);
		transform.setRotation(state.orientation);
		rigid_body->setWorldTransform(transform);

		rigid_body->setLinearVelocity(state.velocity);
		rigid_body->setAngularVelocity(state.angular_velocity);
	}
};
