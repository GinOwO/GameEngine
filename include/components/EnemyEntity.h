#pragma once

#include <core/SocketManager.h>

#include <components/SharedGlobals.h>
#include <components/Entity.h>
#include <components/LookAtComponent.h>
#include <components/PointLight.h>
#include <components/FollowComponent.h>

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
		this->rec_dmg = 0.05f;
	}

	void input(float delta) override
	{
		if (hp > 0) {
			static Entity *p_ent = static_cast<Entity *>(
				SharedGlobals::player_entity);
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

			static SocketManager &sock_manager =
				SocketManager::get_instance();
			std::string received_data = sock_manager.receive_data();

			int action = -1;
			if (received_data.find("action") != std::string::npos) {
				std::stringstream ss(received_data);
				std::string command;

				std::getline(ss, command, ',');
				ss >> action;
			} else if (received_data.find("reset") !=
				   std::string::npos) {
				p_ent->set_hp(0.0025f * 3);
				this->set_hp(10);
				sock_manager.send_data(get_state());
			}
			switch (action) {
			case 0:
				move_forward(delta);
				break;
			case 1:
				move_backward(delta);
				break;
			case 2:
				move_left(delta);
				break;
			case 3:
				move_right(delta);
				break;
			case 4:
				jump(delta);
				break;
			case 5:
				rotate_left(delta);
				break;
			case 6:
				rotate_right(delta);
				break;
			case 7:
				shoot();
				break;
			default:
				break;
			}

			Entity::input(delta);
		}
	}

	void update(float delta) override
	{
		update_material();

		static SocketManager &sock_manager =
			SocketManager::get_instance();

		sock_manager.send_data(get_state());

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
		state << get_enemy_position_string() << ","
		      << get_player_position_string() << "," << hp << ","
		      << static_cast<Entity *>(SharedGlobals::player_entity)
				 ->get_hp()
		      << "," << (shot_hit ? "True" : "False");
		return state.str();
	}
};