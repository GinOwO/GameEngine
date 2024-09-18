/***************************************************************************
 * @file Mesh.h
 *
 * @brief Declares the Mesh class for representing and handling 3D meshes.
 *
 * This file contains the declaration of the Mesh class, which manages the
 * vertex array object (VAO), vertex buffer object (VBO), and element buffer
 * object (EBO) for rendering 3D meshes. It includes methods for creating,
 * drawing, and deleting meshes.
 *
 ***************************************************************************/

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

/***************************************************************************
 * @class Mesh
 *
 * @brief Represents a 3D mesh with vertices and indices.
 *
 * The Mesh class handles the creation, drawing, and deletion of 3D mesh data,
 * including vertex and index buffers. It supports normal calculations and
 * loading meshes from files.
 *
 ***************************************************************************/
class Mesh {
    private:
	std::shared_ptr<MeshResource> buffers;
	static std::unordered_map<std::string, std::weak_ptr<MeshResource> >
		mesh_cache;

	/***************************************************************************
	 * @brief Calculates normals for the mesh vertices.
	 *
	 * @param vertices The vertices of the mesh.
	 * @param indices The indices of the mesh.
	 ***************************************************************************/
	void calculate_normals(std::vector<Vertex> &vertices,
			       std::vector<int> &indices);

    public:
	Mesh();
	Mesh(const std::vector<Vertex> &vertices,
	     const std::vector<int> &indices, bool normals = false);

	/***************************************************************************
	 * @brief Draws the mesh.
	 ***************************************************************************/
	void draw() const;

	/***************************************************************************
	 * @brief Assigns a new MeshResource to this Mesh
	 ***************************************************************************/
	void reset_mesh();

	/***************************************************************************
	 * @brief Adds vertices and indices to the mesh.
	 *
	 * @param vertices The vertices to add.
	 * @param indices The indices to add.
	 * @param normals Whether to calculate normals.
	 ***************************************************************************/
	void add_vertices(std::vector<Vertex> vertices,
			  std::vector<int> indices, bool normals = false);

	/***************************************************************************
	 * @brief Loads a mesh from a file.
	 *
	 * @param file_path The path to the mesh file.
	 * @return The loaded Mesh.
	 ***************************************************************************/
	static Mesh load_mesh(const std::string &file_path);
};
