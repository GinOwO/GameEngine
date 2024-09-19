#pragma once

#include <math/Vector2f.h>
#include <math/Vector3f.h>
#include <graphics/mesh_models/IndexedModel.h>

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class FBXModel {
    private:
	void process_node(aiNode *node, const aiScene *scene,
			  std::vector<Vector3f> &positions,
			  std::vector<Vector2f> &texCoords,
			  std::vector<Vector3f> &normals,
			  std::vector<IndexedModel::Index> &indices);
	void process_mesh(aiMesh *mesh, const aiScene *scene,
			  std::vector<Vector3f> &positions,
			  std::vector<Vector2f> &texCoords,
			  std::vector<Vector3f> &normals,
			  std::vector<IndexedModel::Index> &indices);

    public:
	std::vector<Vector3f> positions;
	std::vector<Vector3f> normals;
	std::vector<Vector2f> texCoords;
	std::vector<IndexedModel::Index> indices;
	bool has_normals;
	bool has_texCoords;

	FBXModel(const std::string &file_path);
	IndexedModel to_indexed_model();
};
