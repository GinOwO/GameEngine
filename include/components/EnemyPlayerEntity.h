#pragma once
#ifdef MULTIPLAYER

#include <core/SharedGlobals.h>

#include <components/Entity.h>
#include <components/LookAtComponent.h>
#include <components/PointLight.h>

#include <misc/SafeQueue.h>

#include <utility>

class EnemyPlayerEntity : public Entity {
    public:
	PlayerEntity()
		: Entity("./assets/objects/Main_model.fbx",
			 "./assets/objects/Main_model_100.png", false)
	{
		this->add_child((new GameObject())
					->add_component(new PointLight(
						"#def", 1.0f, { 0, 0, 0.02f }))
					->add_component(new FollowComponent(
						{ 0, -0.5, 10 }, &transform)));
		this->set_hp(100.0f);
		this->rec_dmg = 0.0025f;
	}

	void input(float delta) override
	{
		static Input &input_handler = Input::get_instance();
		static Timer &timer = Timer::get_instance();
		static SharedGlobals &globals = SharedGlobals::get_instance();

		if (globals.enemy_moves) {
			SafeQueue<std::pair<int32_t, float> > *safe_queue =
				static_cast<
					SafeQueue<std::pair<int32_t, float> > *>(
					globals.enemy_moves);

			if (!queue->empty() && hp > 0) {
				auto [action, delta] = safe_queue.pop();
				switch (action) {
				case 0:
					move_forward(delta);
					break;
				case 1:
					move_left(delta);
					break;
				case 2:
					move_backward(delta);
					break;
				case 3:
					move_right(delta);
					break;
				case 4:
					rotate_left(delta);
					break;
				case 5:
					rotate_right(delta);
					break;
				case 6:
					shoot();
					break;
				case 7:
					jump(delta);
				default:
					break;
				}
			}
		}
		on_ground = false;
		Entity::input(delta);
	}

	void update(float delta) override
	{
		static Material &mat = mesh->get_material();
		static int32_t old_stage = 4, new_stage = 4;
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
		Entity::update(delta);
	}
};
#endif