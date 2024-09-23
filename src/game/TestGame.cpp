#include <game/TestGame.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <math/Vector3f.h>

#include <graphics/Mesh.h>
#include <graphics/Texture.h>
#include <graphics/Material.h>

#include <components/CameraObject.h>
#include <components/FreeLook.h>
#include <components/FreeMove.h>
#include <components/LookAtComponent.h>
#include <components/DirectionalLight.h>
#include <components/PointLight.h>
#include <components/SpotLight.h>
#include <components/MeshRenderer.h>
#include <components/Skybox.h>
#include <components/Person.h>
#include <components/Terrain.h>

#include <cmath>
#include <iostream>

void TestGame::init()
{
	auto &transform = get_root_object()->transform;

	GameObject *skybox = new Skybox(
		"./assets/Skybox/fskybg/source/skybox.fbx",
		"./assets/Skybox/fskybg/textures/background.jpg", { .5 });

	std::map<std::string, std::string> tex_paths;
	tex_paths["diffuse"] = "./assets/terrain/Baking.jpg";

	GameObject *floor =
		new Terrain("./assets/terrain/floor.fbx", tex_paths);

	DirectionalLight *dl = new DirectionalLight("#18f", 0.1f);
	GameObject *lighting_object2 = new GameObject();
	lighting_object2->add_component(dl)->transform.set_rotation(
		Quaternion::Rotation_Quaternion({ 1, 0, 0 },
						to_radians(90.0f)));

	get_root_object()->add_child(lighting_object2);

	GameObject *player_object = new Person(
		"assets/Player E04.fbx", "assets/objects/test_texture.png");

	// player_object->add_component(new FreeMove{ 1.0f, 1.0f, 1.0f });
	Person *player_object1 = new Person("assets/Player E04.fbx",
					    "assets/objects/test_texture.png");
	player_object1->player = true;

	GameObject *lighting_object = new GameObject();
	lighting_object
		->add_component(new PointLight("#fff", 1.0f, { 0, 0, 0.01f }))
		->add_component(new FollowComponent(
			{ 0, -0.5, 12 }, &player_object1->transform));
	CameraObject *camera_object = new CameraObject(
		75.0f, { 0, 3, 2 },
		{ -0.789864, -0.000487476, -0.00402385, -0.613269 }, { 0 },
		{ 10, 10 }, &player_object1->transform);
	SharedGlobals::get_instance().main_camera =
		static_cast<void *>(camera_object->camera);

	get_root_object()
		->add_child(player_object)
		->add_child(skybox)
		->add_child(floor)
		->add_child(player_object1->add_child(camera_object)
				    ->add_child(lighting_object));

	SharedGlobals::get_instance().active_ambient_light = .1;

	get_root_object()->add_to_rendering_engine();
}
