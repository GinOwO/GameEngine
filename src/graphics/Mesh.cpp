#include <graphics/Mesh.h>

#include <misc/glad.h>
#include <GLFW/glfw3.h>

#include <graphics/Vertex.h>
#include <graphics/Material.h>
#include <graphics/mesh_models/OBJModel.h>
#include <graphics/resource_management/MeshResource.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <regex>
#include <exception>

// clang-format off
std::regex extension_regex(R"(.*\.obj$)");
// clang-format on

std::unordered_map<std::string, std::weak_ptr<MeshResource> > Mesh::mesh_cache{};

/***************************************************************************
 * @brief Loads a mesh from a file.
 *
 * Reads a mesh from the specified file path. Supports only OBJ file format.
 *
 * @param file_path The path to the file from which to load the mesh.
 * @return A Mesh object initialized with the loaded vertices and indices.
 * @throws std::runtime_error If the file type is not supported or the file 
 *			     does not exist.
 ***************************************************************************/
Mesh Mesh::load_mesh(const std::string &file_path)
{
	Mesh mesh;
	if (Mesh::mesh_cache.count(file_path)) {
		std::shared_ptr<MeshResource> resource =
			Mesh::mesh_cache[file_path].lock();
		if (resource) {
			mesh.buffers = resource;
			return mesh;
		}
	}

	if (mesh.buffers == nullptr) {
		mesh.reset_mesh();
		mesh_cache[file_path] = mesh.buffers;
	}

	if (!std::regex_match(file_path, extension_regex)) {
		std::cerr << "Error: File type is not supported: " << file_path
			  << '\n';
		throw std::runtime_error("File type is not supported");
		throw std::runtime_error("File type is not supported");
	}

	std::ifstream file(file_path);
	if (!file.good()) {
		std::cerr << "File does not exist: " << file_path << '\n';
		throw std::runtime_error("File does not exist");
		throw std::runtime_error("File does not exist");
	}

	IndexedModel model = OBJModel{ file }.to_indexed_model();
	std::vector<Vertex> vertices;

	for (int i = 0; i < model.positions.size(); i++) {
		vertices.push_back({ model.positions[i], model.texCoords[i],
				     model.normals[i] });
	}
	mesh.add_vertices(vertices, model.indices, false);
	return mesh;
}

/***************************************************************************
 * @brief Default constructor for Mesh.
 *
 * Initializes a Mesh object with default values.
 ***************************************************************************/
Mesh::Mesh() {};

/***************************************************************************
 * @brief Constructs a Mesh with specified vertices, indices, and optional normals.
 *
 * Initializes a Mesh object with the provided vertices and indices. If 
 * `normals` is true, the mesh will also calculate normals.
 *
 * @param vertices The vertices to be used in the mesh.
 * @param indices The indices to be used in the mesh.
 * @param normals Whether to calculate normals for the mesh.
 ***************************************************************************/
Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<int> &indices,
	   bool normals)
{
	this->add_vertices(vertices, indices, normals);
}

/***************************************************************************
 * @brief Acquires a new mesh resource.
 *
 * Assigns a new MeshResource to this Mesh
 ***************************************************************************/
void Mesh::reset_mesh()
{
	this->buffers = std::make_shared<MeshResource>();
}

/***************************************************************************
 * @brief Adds vertices and indices to the mesh.
 *
 * Updates the mesh with the specified vertices and indices. Optionally 
 * calculates normals if `normals` is true.
 *
 * @param vertices The vertices to be added to the mesh.
 * @param indices The indices to be added to the mesh.
 * @param normals Whether to calculate normals for the mesh.
 ***************************************************************************/
void Mesh::add_vertices(std::vector<Vertex> vertices, std::vector<int> indices,
			bool normals)
{
	if (buffers == nullptr) {
		this->reset_mesh();
	}
	if (buffers->size) {
		std::cerr << "Existing Mesh Found, creating new Mesh\n";
		this->reset_mesh();
	}
	if (normals) {
		this->calculate_normals(vertices, indices);
	}

	buffers->size = vertices.size();
	buffers->isize = indices.size();

	std::vector<float> buffer(buffers->size * Vertex::SIZE);

	int i = 0;
	for (const Vertex &v : vertices) {
		Vector3f pos = v.get_pos();
		Vector3f normal = v.get_normal();
		Vector2f texCoord = v.get_texCoord();
		buffer[i++] = pos.getX();
		buffer[i++] = pos.getY();
		buffer[i++] = pos.getZ();
		buffer[i++] = texCoord.getX();
		buffer[i++] = texCoord.getY();
		buffer[i++] = normal.getX();
		buffer[i++] = normal.getY();
		buffer[i++] = normal.getZ();
	}

	glGenVertexArrays(1, &buffers->vao);
	glBindVertexArray(buffers->vao);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &buffers->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, buffers->vbo);
	glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float),
		     buffer.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			      Vertex::SIZE * sizeof(float), (void *)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
			      Vertex::SIZE * sizeof(float), (void *)12);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
			      Vertex::SIZE * sizeof(float), (void *)20);

	glGenBuffers(1, &buffers->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int),
		     indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

/***************************************************************************
 * @brief Draws the mesh.
 *
 * Renders the mesh using the currently bound VAO.
 * @throws std::runtime_error If the VAO is not initialized.
 ***************************************************************************/
void Mesh::draw() const
{
	if (buffers->vao == 0) {
		std::cerr << "VAO not initialized\n";
		throw std::runtime_error("VAO not initialized\n");
		throw std::runtime_error("VAO not initialized\n");
	}

	glBindVertexArray(buffers->vao);
	glDrawElements(GL_TRIANGLES, buffers->isize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

/***************************************************************************
 * @brief Calculates normals for the mesh vertices.
 *
 * Computes normals for each vertex based on the mesh indices and updates
 * the vertex normals.
 *
 * @param vertices The vertices of the mesh.
 * @param indices The indices of the mesh.
 ***************************************************************************/
void Mesh::calculate_normals(std::vector<Vertex> &vertices,
			     std::vector<int> &indices)
{
	for (int i = 0; i < indices.size(); i += 3) {
		int a = indices[i], b = indices[i + 1], c = indices[i + 2];
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
