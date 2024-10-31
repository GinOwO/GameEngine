#pragma once

#include <math/Vector2f.h>
#include <math/Vector3f.h>

#include <graphics/mesh_models/IndexedModel.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/anim.h>
#include <assimp/postprocess.h>

#include <vector>
#include <array>
#include <string>

class FBXModel {
    private:
	void process_node(aiNode *node, const aiScene *scene,
			  std::vector<Vector3f> &positions,
			  std::vector<Vector2f> &texCoords,
			  std::vector<Vector3f> &normals,
			  std::vector<std::array<int32_t, 4> > &bone_indices,
			  std::vector<std::array<float, 4> > &bone_weights,
			  std::vector<IndexedModel::Index> &indices);
	void process_mesh(aiMesh *mesh, const aiScene *scene,
			  std::vector<Vector3f> &positions,
			  std::vector<Vector2f> &texCoords,
			  std::vector<Vector3f> &normals,
			  std::vector<IndexedModel::Index> &indices,
			  std::vector<std::array<int32_t, 4> > &boneIndices,
			  std::vector<std::array<float, 4> > &boneWeights);

    public:
	std::vector<Vector3f> positions;
	std::vector<Vector3f> normals;
	std::vector<Vector2f> texCoords;
	std::vector<std::array<float, 4> > bone_weights;
	std::vector<std::array<int32_t, 4> > bone_indices;
	std::vector<IndexedModel::Index> indices;
	bool has_normals;
	bool has_texCoords;

	FBXModel(const std::string &file_path);
	IndexedModel to_indexed_model();
};
