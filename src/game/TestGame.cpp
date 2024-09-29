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
#include <components/PointLight.h>
#include <components/DirectionalLight.h>
#include <components/SpotLight.h>
#include <components/MeshRenderer.h>
#include <components/Skybox.h>
#include <components/PlayerEntity.h>
#include <components/EnemyEntity.h>
#include <components/Terrain.h>
#include <components/ArcBall.h>

#include <iostream>
#include <cmath>

const std::unordered_map<std::string, std::string> mesh_assets = {
	{ "skybox", "./assets/Skybox/fskybg/source/skybox.fbx" },
	{ "terrain_test", "./assets/terrain/test_floor.fbx" },
	{ "arena", "./assets/terrain/arena.fbx" },
	{ "player", "./assets/Player E04.fbx" },
	{ "mech", "./assets/objects/Main_model.fbx" },
	{ "bullet", "./assets/objects/bullet.fbx" }
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

	Entity *player_entity = new PlayerEntity();

	Entity *enemy_entity = new EnemyEntity();

	CameraObject *camera_object = new CameraObject(85.0f);

	camera_object->add_component(
		new ArcBall(&player_entity->transform, 6.5f));

	SharedGlobals::get_instance().main_camera =
		static_cast<void *>(camera_object->camera);

	get_root_object()
		->add_child(skybox)
		->add_child(floor)
		->add_child(player_entity)
		->add_child(enemy_entity)
		->add_child(camera_object);

	SharedGlobals::get_instance().active_ambient_light = .2;

	get_root_object()->add_to_rendering_engine();
}
