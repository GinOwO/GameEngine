#pragma once

#include <components/SharedGlobals.h>
#include <components/Entity.h>
#include <components/LookAtComponent.h>
#include <components/PointLight.h>

class EnemyEntity : public Entity {
	float shooting_range = 50.0f;
	float time_since_last_shot = 0.0f;
	float shooting_interval = 0.05f;

    public:
	EnemyEntity()
		: Entity("assets/objects/Main_model.fbx",
			 "assets/objects/Main_model_100.png", false)
	{
		this->add_child((new GameObject())
					->add_component(new PointLight(
						"#fed", 1.0f, { 0, 0, 0.02f }))
					->add_component(new FollowComponent(
						{ 0, -0.5, 10 }, &transform)));
		this->set_hp(100.0f);
		this->rec_dmg = 0.025f;
	}

	void input(float delta) override
	{
		if (hp > 0) {
			shoot();
			Entity::input(delta);
		}
	}

	void update(float delta) override
	{
		update_material();

		Entity::update(delta);
	}

	void move_forward(float delta)
	{
		move(transform.get_rotation().get_forward(),
		     move_impulse_factor * delta);
	}
	void move_left(float delta)
	{
		move(transform.get_rotation().get_left(),
		     move_impulse_factor * delta);
	}
	void move_backward(float delta)
	{
		move(transform.get_rotation().get_backward(),
		     move_impulse_factor * delta);
	}
	void move_right(float delta)
	{
		move(transform.get_rotation().get_right(),
		     move_impulse_factor * delta);
	}
	void rotate_left(float delta)
	{
		rotate(Vector3f::z_axis, rotate_impulse_factor * delta);
	}
	void rotate_right(float delta)
	{
		rotate(Vector3f::z_axis, -rotate_impulse_factor * delta);
	}

    private:
	void update_material()
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
	}
};