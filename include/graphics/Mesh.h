#pragma once

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Vertex.h>
#include <graphics/Material.h>
#include <graphics/resource_management/MeshResource.h>

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

class Mesh {
    private:
	std::shared_ptr<MeshResource> buffers;

	void calculate_normals(std::vector<Vertex> &vertices,
			       std::vector<int> &indices);

    public:
	enum class MeshPhysicsType {
		NO_PHYSICS,
		ENTITY,
		TERRAIN
	} mesh_physics_type;

	Mesh();
	Mesh(const std::vector<Vertex> &vertices,
	     const std::vector<int> &indices, bool normals = false,
	     MeshPhysicsType mesh_physics_type = MeshPhysicsType::NO_PHYSICS);

	void draw() const;

	void reset_mesh();

	void update_physics(int id);

	void add_vertices(std::vector<Vertex> vertices,
			  std::vector<int> indices, bool normals = false,
			  MeshPhysicsType mesh_physics_type =
				  MeshPhysicsType::NO_PHYSICS);

	static Mesh load_mesh(const std::string &file_path,
			      MeshPhysicsType mesh_physics_type =
				      MeshPhysicsType::NO_PHYSICS);

	static void pre_load(const std::string &file_path);
};
