#include <game/TestGame.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <math/Vector3f.h>

#include <graphics/Mesh.h>
#include <graphics/Vertex.h>
#include <graphics/Texture.h>
#include <graphics/Material.h>

#include <components/Camera.h>
#include <components/FreeLook.h>
#include <components/FreeMove.h>
#include <components/LookAtComponent.h>
#include <components/DirectionalLight.h>
#include <components/PointLight.h>
#include <components/SpotLight.h>
#include <components/MeshRenderer.h>
#include <components/Skybox.h>

#include <cmath>
#include <iostream>

void TestGame::init()
{
	auto &transform = get_root_object()->transform;

	GameObject *camera_object = new GameObject();
	Camera *camera = new Camera();
	SharedGlobals::get_instance().main_camera = static_cast<void *>(camera);
	camera_object->add_component(new FreeMove(2.0f))
		->add_component(new FreeLook(5.0f))
		->add_component(camera);

	camera_object->transform.set_translation({ 5, 0, -10 });

	GameObject *skybox = new Skybox(
		"./assets/Skybox/fskybg/source/skybox.fbx",
		"./assets/Skybox/fskybg/textures/background.jpg", { .5 });
	skybox->transform.set_scale(5).set_rotation(
		Quaternion::Rotation_Quaternion({ 0, 1, 0 },
						to_radians(45.0f)));

	GameObject *floor = new GameObject();
	Material floor_material;
	Mesh floor_mesh = Mesh::load_mesh("./assets/floor.fbx");

	const std::string floor_paths[] = {
		"./assets/terrain/dry_riverbed_rock/textures/dry_riverbed_rock_diff_1k.jpg",
		"./assets/terrain/dry_riverbed_rock/textures/dry_riverbed_rock_disp_1k.png",
		"./assets/terrain/dry_riverbed_rock/textures/dry_riverbed_rock_nor_gl_1k.exr",
		"./assets/terrain/dry_riverbed_rock/textures/dry_riverbed_rock_rough_1k.exr"
	};

	const char *types[] = { "diffuse", "displacement", "normal",
				"roughness" };

	for (int i = 0; i < 4; i++) {
		floor_material.add_property(
			types[i], Texture::load_texture(floor_paths[i]));
	}

	floor_material.add_property("specular",
				    std::shared_ptr<void>(new Specular{ 1, 8 },
							  Specular::deleter));

	floor->add_component(new MeshRenderer(floor_mesh, floor_material));

	// GameObject *lighting_object = new GameObject();
	// DirectionalLight *dl = new DirectionalLight("#0ff", 0.7f);
	// lighting_object->add_component(dl)->transform.set_rotation(
	// 	Quaternion::Rotation_Quaternion({ 1, 0, 0 },
	// 					to_radians(135.0f)));
	// get_root_object()->add_child(lighting_object);

	get_root_object()->add_child(camera_object);
	get_root_object()->add_child(skybox);
	get_root_object()->add_child(floor);

	camera_object->transform
		.set_rotation(Quaternion::Rotation_Quaternion(
			{ 1, 0, 0 }, to_radians(135.0f)))
		.set_translation({ 0, 30, 30 })
		.set_scale(3);

	SharedGlobals::get_instance().active_ambient_light = 1;

	get_root_object()->add_to_rendering_engine();
}
