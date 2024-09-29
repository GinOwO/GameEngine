#pragma once

#include <components/Entity.h>
#include <components/LookAtComponent.h>
#include <components/PointLight.h>

class PlayerEntity : public Entity {
    public:
	PlayerEntity()
		: Entity("assets/objects/Main_model.fbx",
			 "assets/objects/Main_model_100.png", true)
	{
		this->add_child((new GameObject())
					->add_component(new PointLight(
						"#def", 1.0f, { 0, 0, 0.02f }))
					->add_component(new FollowComponent(
						{ 0, -0.5, 10 }, &transform)));
		this->set_hp(100.0f);
		this->rec_dmg = 0.0025f;
		SharedGlobals::get_instance().player_transform = &transform;
	}

	void input(float delta) override
	{
		static Input &input_handler = Input::get_instance();
		static Timer &timer = Timer::get_instance();
		if (player && hp > 0) {
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
			if (input_handler.is_mouse_down(GLFW_MOUSE_BUTTON_1)) {
				shoot();
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
		Entity::input(delta);
	}

	void update(float delta) override
	{
		static Material &mat = mesh->get_material();
		static int old_stage = 4, new_stage = 4;
		static const std::string diffuses[] = {
			"assets/objects/Main_model_0.png",
			"assets/objects/Main_model_25.png",
			"assets/objects/Main_model_50.png",
			"assets/objects/Main_model_75.png",
			"assets/objects/Main_model_100.png"
		};

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