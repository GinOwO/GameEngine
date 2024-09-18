#include <game/TestGame.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <math/Vector3f.h>

#include <graphics/Mesh.h>
#include <graphics/Vertex.h>
#include <graphics/Texture.h>
#include <graphics/Material.h>

#include <components/Camera.h>
#include <components/DirectionalLight.h>
#include <components/PointLight.h>
#include <components/SpotLight.h>
#include <components/MeshRenderer.h>

#include <cmath>
#include <iostream>

void TestGame::init()
{
	auto &transform = get_root_object()->transform;

	float field_width = 10.0f, field_depth = 10.0f;
	std::vector<Vertex> vertices{
		{ { -field_width, 0.0f, -field_depth }, { 0.0f, 0.0f } },
		{ { -field_width, 0.0f, field_depth * 3 }, { 0.0f, 1.0f } },
		{ { field_width * 3, 0.0f, -field_depth }, { 1.0f, 0.0f } },
		{ { field_width * 3, 0.0f, field_depth * 3 }, { 1.0f, 1.0f } }
	};

	std::vector<int> indices{ 0, 1, 2, 2, 1, 3 };

	field_width = 1;
	field_depth = 1;
	std::vector<Vertex> vertices2{
		{ { -field_width, 0.0f, -field_depth }, { 0.0f, 0.0f } },
		{ { -field_width, 0.0f, field_depth * 3 }, { 0.0f, 1.0f } },
		{ { field_width * 3, 0.0f, -field_depth }, { 1.0f, 0.0f } },
		{ { field_width * 3, 0.0f, field_depth * 3 }, { 1.0f, 1.0f } }
	};

	Mesh mesh(vertices, indices, true);
	Mesh mesh2(vertices2, indices, true);
	Mesh mesh3 = Mesh::load_mesh("./assets/objects/monkey.obj");
	Mesh mesh4 = Mesh::load_mesh("./assets/objects/monkey.obj");
	Material material, material2;
	Texture *tex =
		Texture::load_texture("./assets/objects/test_texture.png");
	Texture *tex2 =
		Texture::load_texture("./assets/objects/test_texture.png");

	material.add_property("diffuse",
			      std::shared_ptr<void>(tex, Texture::deleter));
	material.add_property(
		"specular",
		std::shared_ptr<void>(new Specular{ 1, 8 }, [](void *ptr) {
			delete static_cast<Specular *>(ptr);
		}));

	material2.add_property("diffuse",
			       std::shared_ptr<void>(tex2, Texture::deleter));
	material2.add_property(
		"specular",
		std::shared_ptr<void>(new Specular{ 1, 8 }, [](void *ptr) {
			delete static_cast<Specular *>(ptr);
		}));

	GameObject *camera_object = new GameObject();
	Camera *camera = new Camera();
	SharedGlobals::get_instance().main_camera = camera;
	camera_object->add_component(camera);

	GameObject *plane_object = new GameObject();
	plane_object->add_component(new MeshRenderer(mesh, material));
	plane_object->transform.set_translation(0, -1, 5);

	GameObject *light_object0 = new GameObject();
	DirectionalLight *directional_light =
		new DirectionalLight{ "#00F", 0.4f };
	light_object0->add_component(directional_light);
	light_object0->transform.set_rotation(Quaternion::Rotation_Quaternion(
		{ 1, 0, 0 }, to_radians(-135.0f)));

	light_object0->transform.set_translation({ 0, 0, -10 });

	GameObject *light_object1 = new GameObject();
	PointLight *point_light = new PointLight{
		"#0F0",
		0.4f,
		{ 0, 0, 1 },
	};
	light_object1->add_component(point_light);
	light_object1->transform.set_translation(1, 0, 1);

	GameObject *light_object2 = new GameObject();
	SpotLight *spot_light =
		new SpotLight{ "#0Ff", 0.4f, { 0, 0, 0.1f }, 0.7f };
	light_object2->add_component(spot_light);
	light_object2->transform.set_translation(5, 0, 5);
	light_object2->transform.set_rotation(Quaternion::Rotation_Quaternion(
		{ 0, 1, 0 }, to_radians(90.0f)));

	get_root_object()->add_child(plane_object);
	get_root_object()->add_child(light_object0);
	get_root_object()->add_child(light_object1);
	get_root_object()->add_child(light_object2);
	get_root_object()->add_child(camera_object);

	camera_object->transform.set_translation({ 5, 0, -10 });

	GameObject *monkey1 = new GameObject();
	monkey1->add_component(new MeshRenderer(mesh3, material));
	monkey1->transform
		.set_rotation(Quaternion::Rotation_Quaternion(
			{ 0, 1, 0 }, to_radians(180.0f)))
		.set_scale(4)
		.set_translation(5, 5, 5);
	plane_object->add_child(monkey1);

	GameObject *monkey2 = new GameObject();
	monkey2->add_component(new MeshRenderer(mesh4, material2));
	monkey2->transform
		.set_rotation(Quaternion::Rotation_Quaternion(
			{ 0, 1, 0 }, to_radians(180.0f)))
		.set_scale(4)
		.set_translation(20, 5, 5);
	plane_object->add_child(monkey2);
}
