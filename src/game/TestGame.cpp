#include <game/TestGame.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <math/Vector3f.h>

#include <graphics/Mesh.h>
#include <graphics/Vertex.h>
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

#include <cmath>
#include <iostream>

void TestGame::init()
{
	auto &transform = get_root_object()->transform;

	GameObject *skybox = new Skybox(
		"./assets/Skybox/fskybg/source/skybox.fbx",
		"./assets/Skybox/fskybg/textures/background.jpg", { .5 });

	const std::string floor_paths[] = {
		"./assets/terrain/Baking.jpg",
	};

	const char *types[] = { "diffuse" };

	GameObject *floor = new GameObject();
	Material floor_material;
	for (int i = 0; i < 1; i++) {
		floor_material.add_property(
			types[i], Texture::load_texture(floor_paths[i]));
	}

	floor_material.add_property("specular",
				    std::shared_ptr<void>(new Specular{ 1, 8 },
							  Specular::deleter));
	floor
		->add_component(new MeshRenderer(
			Mesh::load_mesh("./assets/terrain/floor.fbx"),
			floor_material))
		->transform.set_scale(10);

	DirectionalLight *dl = new DirectionalLight("#18f", 0.1f);
	GameObject *lighting_object2 = new GameObject();
	lighting_object2->add_component(dl)->transform.set_rotation(
		Quaternion::Rotation_Quaternion({ 1, 0, 0 },
						to_radians(90.0f)));
	get_root_object()->add_child(lighting_object2);

	GameObject *player_object = new Person(
		"assets/BASEmodel.fbx", "assets/objects/test_texture.png");

	player_object->add_component(new FreeMove{ 1.0f, 1.0f, 0 });

	GameObject *lighting_object = new GameObject();
	lighting_object
		->add_component(new PointLight("#fff", 1.0f, { 0, 0, 0.01f }))
		->add_component(new FollowComponent({ 0, -0.5, 12 },
						    &player_object->transform));
	CameraObject *camera_object = new CameraObject(
		70.0f, { 0, 7, 5 },
		{ -0.789864, -0.000487476, -0.00402385, -0.613269 }, { 0 },
		{ 10, 10 }, &player_object->transform);
	SharedGlobals::get_instance().main_camera =
		static_cast<void *>(camera_object->camera);

	get_root_object()->add_child(skybox)->add_child(floor)->add_child(
		player_object->add_child(camera_object)
			->add_child(lighting_object));

	SharedGlobals::get_instance().active_ambient_light = .1;

	get_root_object()->add_to_rendering_engine();
}
