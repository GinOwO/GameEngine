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
#include <components/Entity.h>
#include <components/Terrain.h>

#include <cmath>
#include <iostream>

const std::unordered_map<std::string, std::string> mesh_assets = {
	{ "skybox", "./assets/Skybox/fskybg/source/skybox.fbx" },
	{ "terrain_test", "./assets/terrain/test_floor.fbx" },
	{ "arena", "./assets/terrain/arena.fbx" },
	{ "player", "./assets/Player E04.fbx" },
	{ "mech", "./assets/objects/Main_model.fbx" }
};

TestGame::TestGame()
	: Game()
{
	for (auto &[_, path] : mesh_assets) {
		Mesh::pre_load(path);
	}
}

void TestGame::init()
{
	auto &transform = get_root_object()->transform;

	GameObject *skybox = new Skybox(
		mesh_assets.at("skybox"),
		"./assets/Skybox/fskybg/textures/background.jpg", { .5 });

	std::map<std::string, std::string> tex_paths;
	tex_paths["diffuse"] = "./assets/terrain/arena.png";

	GameObject *floor = new Terrain(mesh_assets.at("arena"), tex_paths);

	DirectionalLight *dl = new DirectionalLight("#18f", 0.1f);
	GameObject *lighting_object2 = new GameObject();
	lighting_object2->add_component(dl)->transform.set_rotation(
		Quaternion::Rotation_Quaternion({ 1, 0, 0 },
						to_radians(90.0f)));

	get_root_object()->add_child(lighting_object2);

	// Person *player_object = new Person("assets/Player E04.fbx",
	// 				   "assets/objects/test_texture.png");

	// player_object->move(
	// 	player_object->transform.get_rotation().get_forward(), 10.0f);
	// player_object->update_physics();
	// get_root_object()->add_child(player_object);

	// player_object->add_component(new FreeMove{ 1.0f, 1.0f, 1.0f });

	Entity *player_object1 = new Entity(mesh_assets.at("mech"),
					    "assets/objects/test_texture.png",
					    true);

	GameObject *lighting_object = new GameObject();
	lighting_object
		->add_component(new PointLight("#fff", 1.0f, { 0, 0, 0.02f }))
		->add_component(new FollowComponent(
			{ 0, -0.5, 10 }, &player_object1->transform));

	CameraObject *camera_object = new CameraObject(
		75.0f, { 0, 0, 0 },
		{ -0.82597, -0.00809713, -0.000692113, -0.563655 }, { 1 },
		{ 10, 10 });

	camera_object->transform.set_translation({ 0, 30, 20 });

	SharedGlobals::get_instance().main_camera =
		static_cast<void *>(camera_object->camera);

	get_root_object()
		->add_child(skybox)
		->add_child(floor)
		->add_child(player_object1->add_child(lighting_object))
		->add_child(camera_object);

	SharedGlobals::get_instance().active_ambient_light = .1;

	get_root_object()->add_to_rendering_engine();
}
