#include <graphics/Mesh.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Vertex.h>
#include <graphics/Material.h>
#include <graphics/mesh_models/OBJModel.h>
#include <graphics/mesh_models/FBXModel.h>
#include <graphics/resource_management/MeshResource.h>

#include <core/SharedGlobals.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <exception>

std::unordered_map<std::string, int32_t> loaded_file_ids;

std::unordered_map<int32_t, std::weak_ptr<MeshResource> > mesh_cache{};

std::unordered_map<int32_t,
		   std::pair<std::vector<btScalar>, std::vector<int32_t> > >
	all_bullet_vertices{};

std::unordered_map<int32_t, std::vector<Vertex> > all_vertices{};

void Mesh::pre_load(const std::string &file_path)
{
	if (loaded_file_ids.count(file_path))
		return;

	static int32_t id = -1;
	loaded_file_ids[file_path] = ++id;
	std::cout << "Preloading Mesh Asset (" << id << "): " << file_path
		  << "\r\n";

	IndexedModel model;
	if (file_path.ends_with(".obj")) {
		std::ifstream file(file_path);
		if (!file.good()) {
			std::cerr << "File does not exist: " << file_path
				  << "\r\n";
			throw std::runtime_error("File does not exist");
		}
		file.close();

		model = OBJModel{ file_path }.to_indexed_model();
	} else if (file_path.ends_with(".fbx")) {
		model = FBXModel{ file_path }.to_indexed_model();
	} else {
		std::cerr << "Error: File type is not supported: " << file_path
			  << "\r\n";
		throw std::runtime_error("File type is not supported");
	}

	std::cout << "Preloading (" << id << "): Loaded into memory\r\n";

	all_vertices[id] = {};
	auto &vertices = all_vertices[id];

	for (int32_t i = 0; i < model.positions.size(); i++) {
		Vertex vertex(model.positions[i], model.texCoords[i],
			      model.normals[i]);
		vertex.boneIndices = model.bone_indices[i];
		vertex.boneWeights = model.bone_weights[i];
		vertices.push_back(vertex);
	}

	all_bullet_vertices[id] = { {}, model.indices };
	auto &[bullet_vertices, _] = all_bullet_vertices[id];
	for (Vertex &vertex : vertices) {
		bullet_vertices.push_back(vertex.get_pos().getX());
		bullet_vertices.push_back(vertex.get_pos().getY());
		bullet_vertices.push_back(vertex.get_pos().getZ());
	}

	std::cout << "Preloading (" << id << "): Done\r\n";
}

Mesh Mesh::load_mesh(const std::string &file_path,
		     MeshPhysicsType mesh_physics_type)
{
	pre_load(file_path);
	int32_t id = loaded_file_ids[file_path];

	Mesh mesh;
	mesh.mesh_physics_type = mesh_physics_type;
	if (mesh_cache.count(id)) {
		std::shared_ptr<MeshResource> resource = mesh_cache[id].lock();
		if (resource) {
			mesh.buffers = resource;
			mesh.update_physics(id);
			return mesh;
		}
	}

	if (mesh.buffers == nullptr) {
		mesh.reset_mesh();
		mesh_cache[id] = mesh.buffers;
	}

	mesh.add_vertices(all_vertices[id], all_bullet_vertices[id].second,
			  false, mesh_physics_type);

	mesh.update_physics(id);

	return mesh;
}

void Mesh::update_physics(int32_t id)
{
	btRigidBody *rigid_body = nullptr;
	SharedGlobals &globals = SharedGlobals::get_instance();
	auto &[bullet_vertices, indices] = all_bullet_vertices.at(id);

	switch (mesh_physics_type) {
	case Mesh::MeshPhysicsType::ENTITY: {
		btConvexHullShape *shape = new btConvexHullShape(
			bullet_vertices.data(),
			static_cast<int32_t>(bullet_vertices.size() / 3),
			sizeof(btScalar) * 3);

		btDefaultMotionState *motion_state = new btDefaultMotionState();
		btScalar mass = 200.0f;
		btVector3 inertia(0, 0, 0);
		shape->calculateLocalInertia(mass, inertia);
		// shape->setMargin(5e-5);

		btRigidBody::btRigidBodyConstructionInfo rigid_body_info(
			mass, motion_state, shape, inertia);
		rigid_body = new btRigidBody(rigid_body_info);
		rigid_body->setDamping(0.2f, 0.0f);
		break;
	}

	case Mesh::MeshPhysicsType::TERRAIN: {
		auto *index_vertex_array = new btTriangleIndexVertexArray(
			static_cast<int32_t>(indices.size() / 3),
			indices.data(), sizeof(int32_t) * 3,
			static_cast<int32_t>(bullet_vertices.size() / 3),
			bullet_vertices.data(), sizeof(btScalar) * 3);

		btBvhTriangleMeshShape *shape =
			new btBvhTriangleMeshShape(index_vertex_array, true);
		shape->setMargin(5e-5);
		globals.collision_shapes.push_back(shape);

		btDefaultMotionState *motion_state = new btDefaultMotionState();
		btRigidBody::btRigidBodyConstructionInfo rigid_body_info(
			0, motion_state, shape, btVector3(0, 0, 0));
		rigid_body = new btRigidBody(rigid_body_info);
		break;
	}

	case MeshPhysicsType::NO_PHYSICS:
	default:
		break;
	}
	if (rigid_body != nullptr) {
		globals.dynamics_world->addRigidBody(rigid_body);
	}
	globals.current_rigid_body = rigid_body;
}

void Mesh::add_vertices(std::vector<Vertex> vertices,
			std::vector<int32_t> indices, bool normals,
			MeshPhysicsType mesh_physics_type)
{
	if (buffers == nullptr) {
		this->reset_mesh();
	}
	if (buffers->size) {
		std::cerr << "Existing Mesh Found, creating new Mesh\r\n";
		this->reset_mesh();
	}
	if (normals) {
		this->calculate_normals(vertices, indices);
	}

	buffers->size = vertices.size();
	buffers->isize = indices.size();

	std::vector<float> buffer(buffers->size * Vertex::SIZE);

	int32_t i = 0;
	for (const Vertex &v : vertices) {
		Vector3f pos = v.get_pos();
		Vector3f normal = v.get_normal();
		Vector2f tex_coord = v.get_texCoord();
		buffer[i++] = pos.getX();
		buffer[i++] = pos.getY();
		buffer[i++] = pos.getZ();
		buffer[i++] = tex_coord.getX();
		buffer[i++] = tex_coord.getY();
		buffer[i++] = normal.getX();
		buffer[i++] = normal.getY();
		buffer[i++] = normal.getZ();

		for (int32_t j = 0; j < 4; ++j) {
			buffer[i++] = v.boneIndices[j];
		}
		for (int32_t j = 0; j < 4; ++j) {
			buffer[i++] = v.boneWeights[j];
		}
	}

	glGenVertexArrays(1, &buffers->vao);
	glBindVertexArray(buffers->vao);

	glEnableVertexAttribArray(0); // Position
	glEnableVertexAttribArray(1); // TexCoord
	glEnableVertexAttribArray(2); // Normal
	glEnableVertexAttribArray(3); // Bone Indices
	glEnableVertexAttribArray(4); // Bone Weights

	glGenBuffers(1, &buffers->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, buffers->vbo);
	glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float),
		     buffer.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			      Vertex::SIZE * sizeof(float), (void *)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
			      Vertex::SIZE * sizeof(float),
			      (void *)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
			      Vertex::SIZE * sizeof(float),
			      (void *)(5 * sizeof(float)));
	glVertexAttribIPointer(3, 4, GL_INT, Vertex::SIZE * sizeof(float),
			       (void *)(8 * sizeof(float)));
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE,
			      Vertex::SIZE * sizeof(float),
			      (void *)(12 * sizeof(float)));

	glGenBuffers(1, &buffers->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int32_t),
		     indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::Mesh() {};

Mesh::Mesh(const std::vector<Vertex> &vertices,
	   const std::vector<int32_t> &indices, bool normals,
	   MeshPhysicsType mesh_physics_type)
{
	this->mesh_physics_type = mesh_physics_type;
	this->add_vertices(vertices, indices, normals, mesh_physics_type);
}

void Mesh::reset_mesh()
{
	this->buffers = std::make_shared<MeshResource>();
}

void Mesh::draw() const
{
	if (buffers->vao == 0) {
		std::cerr << "VAO not initialized\r\n";
		throw std::runtime_error("VAO not initialized\r\n");
	}

	glBindVertexArray(buffers->vao);
	glDrawElements(GL_TRIANGLES, buffers->isize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::calculate_normals(std::vector<Vertex> &vertices,
			     std::vector<int32_t> &indices)
{
	for (int32_t i = 0; i < indices.size(); i += 3) {
		int32_t a = indices[i], b = indices[i + 1], c = indices[i + 2];
		Vector3f v1 = vertices[b].get_pos() - vertices[a].get_pos();
		Vector3f v2 = vertices[c].get_pos() - vertices[a].get_pos();

		Vector3f normal = v1.cross(v2).normalize();

		vertices[a].set_normal(vertices[a].get_normal() + normal);
		vertices[b].set_normal(vertices[b].get_normal() + normal);
		vertices[c].set_normal(vertices[c].get_normal() + normal);
	}
	for (Vertex &v : vertices) {
		v.set_normal(v.get_normal().normalize());
	}
}
