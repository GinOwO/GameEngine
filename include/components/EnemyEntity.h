#pragma once

#include <core/SocketManager.h>

#include <components/SharedGlobals.h>
#include <components/Entity.h>
#include <components/LookAtComponent.h>
#include <components/PointLight.h>
#include <components/FollowComponent.h>

#define RT_IMP_F 3e3

#ifdef MV_IMP_F
btScalar MOVE_IMPULSE_FACTOR = MV_IMP_F;
#else
btScalar MOVE_IMPULSE_FACTOR = 1.2e4;
#endif

#ifdef RT_IMP_F
btScalar ROTATE_IMPULSE_FACTOR = RT_IMP_F;
#else
btScalar ROTATE_IMPULSE_FACTOR = 2.5e2;
#endif

class EnemyEntity : public Entity {
	bool should_shoot = false;
	bool shot_hit = false;

    public:
	EnemyEntity()
		: Entity("./assets/objects/Main_model.fbx",
			 "./assets/objects/Main_model_100.png", false)
	{
		this->add_child((new GameObject())
					->add_component(new PointLight(
						"#fed", 1.0f, { 0, 0, 0.02f }))
					->add_component(new FollowComponent(
						{ 0, -0.5, 10 }, &transform)));
		this->set_hp(100.0f);
		this->max_hp = 100.0f;
		this->rec_dmg = 0.05f;
		rigid_body->setDamping(0.0f, 0.0f);
		this->move_impulse_factor = MOVE_IMPULSE_FACTOR;
		this->rotate_impulse_factor = ROTATE_IMPULSE_FACTOR;
	}

	void input(float delta) override
	{
#ifndef MULTIPLAYER
		static SocketManager &sock_manager =
			SocketManager::get_instance();
		static Entity *p_ent =
			static_cast<Entity *>(SharedGlobals::player_entity);
		std::string received_data = sock_manager.receive_data();

		int action = -1;
		float factor = 1.0f;
		if (received_data.find("reset") != std::string::npos) {
			p_ent->set_hp(0.0025f * 150);
			p_ent->set_max_hp(0.0025f * 150);
			this->set_hp(0.05f * 300);
			this->set_max_hp(0.05f * 300);
			sock_manager.send_data(get_state());
		} else if (received_data.find("action") != std::string::npos) {
			std::stringstream ss(received_data);
			std::string command;

			std::getline(ss, command, ',');
			ss >> action;
			ss >> factor;
		}
		if (hp > 0) {
			if (should_shoot) {
				float p_hp = p_ent->get_hp();
				Entity::shoot();
				float n_hp = p_ent->get_hp();
				if (n_hp < p_hp) {
					shot_hit = true;
				} else {
					shot_hit = false;
				}
				should_shoot = false;
			}

			if (action == 0) {
				move_forward(delta * factor);
			} else if (action == 1) {
				move_backward(delta * factor);
			} else if (action == 2) {
				move_left(delta * factor);
			} else if (action == 3) {
				move_right(delta * factor);
			} else if (action == 4) {
				shoot();
			} else if (action == 5) {
				rotate_left(delta * factor);
			} else if (action == 6) {
				rotate_right(delta * factor);
			} else if (action == 7) {
				jump(delta * factor);
			}

			Entity::input(delta);
		}
#else
		Entity::input(delta);
#endif
	}

	void update(float delta) override
	{
		update_material();
#ifndef MULTIPLAYER
		static SocketManager &sock_manager =
			SocketManager::get_instance();

		sock_manager.send_data(get_state());
#endif
		Entity::update(delta);
	}

	bool missed_shot()
	{
		bool state = shot_hit;
		shot_hit = false;
		return state;
	}

	void shoot()
	{
		should_shoot = true;
	}

	void get_hit() override
	{
		Entity::get_hit();
	}

    private:
	std::string get_enemy_position_string()
	{
		Vector3f enemy_pos = transform.get_translation();
		return std::to_string(enemy_pos.getX()) + "," +
		       std::to_string(enemy_pos.getY()) + "," +
		       std::to_string(enemy_pos.getZ());
	}

	std::string get_player_position_string()
	{
		if (SharedGlobals::player_entity) {
			Vector3f player_pos =
				static_cast<Entity *>(
					SharedGlobals::player_entity)
					->transform.get_translation();
			return std::to_string(player_pos.getX()) + "," +
			       std::to_string(player_pos.getY()) + "," +
			       std::to_string(player_pos.getZ());
		}
		return "0,0,0";
	}

	std::string get_enemy_rotation_string()
	{
		Quaternion enemy_rot = transform.get_rotation();
		return std::to_string(enemy_rot.getW()) + "," +
		       std::to_string(enemy_rot.getX()) + "," +
		       std::to_string(enemy_rot.getY()) + "," +
		       std::to_string(enemy_rot.getZ());
	}

	std::string get_player_rotation_string()
	{
		if (SharedGlobals::player_entity) {
			Quaternion player_rot =
				static_cast<Entity *>(
					SharedGlobals::player_entity)
					->transform.get_rotation();
			return std::to_string(player_rot.getW()) + "," +
			       std::to_string(player_rot.getX()) + "," +
			       std::to_string(player_rot.getY()) + "," +
			       std::to_string(player_rot.getZ());
		}
		return "0,0,0,0";
	}

	void update_material()
	{
		static Material &mat = mesh->get_material();
		static int old_stage = 4, new_stage = 4;
		static const std::string diffuses[] = {
			"./assets/objects/Main_model_0.png",
			"./assets/objects/Main_model_25.png",
			"./assets/objects/Main_model_50.png",
			"./assets/objects/Main_model_75.png",
			"./assets/objects/Main_model_100.png"
		};

		float hp = this->hp * 100.0f / this->max_hp;
		new_stage =
			4 - (hp <= 75) - (hp <= 50) - (hp <= 25) - (hp <= 0);

		if (new_stage != old_stage) {
			old_stage = new_stage;
			mat.add_property(
				"diffuse",
				Texture::load_texture(diffuses[new_stage]));
		}
	}

	std::string get_state()
	{
		std::stringstream state;
		state << hp << ","
		      << static_cast<Entity *>(SharedGlobals::player_entity)
				 ->get_hp()
		      << "," << get_enemy_position_string() << ","
		      << get_player_position_string() << ","
		      << (shot_hit ? "True" : "False") << ','
		      << get_enemy_rotation_string() << ','
		      << get_player_rotation_string() << ',';
		return state.str();
	}
};