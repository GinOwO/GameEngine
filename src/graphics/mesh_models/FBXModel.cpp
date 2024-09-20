#include <graphics/mesh_models/FBXModel.h>

#include <math/Vector2f.h>
#include <math/Vector3f.h>

#include <graphics/mesh_models/IndexedModel.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>
#include <array>
#include <exception>
#include <stdexcept>

void FBXModel::process_node(aiNode *node, const aiScene *scene,
			    std::vector<Vector3f> &positions,
			    std::vector<Vector2f> &texCoords,
			    std::vector<Vector3f> &normals,
			    std::vector<std::array<int, 4> > &bone_indices,
			    std::vector<std::array<float, 4> > &bone_weights,
			    std::vector<IndexedModel::Index> &indices)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		process_mesh(mesh, scene, positions, texCoords, normals,
			     indices, bone_indices, bone_weights);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		process_node(node->mChildren[i], scene, positions, texCoords,
			     normals, bone_indices, bone_weights, indices);
	}
}

void FBXModel::process_mesh(aiMesh *mesh, const aiScene *scene,
			    std::vector<Vector3f> &positions,
			    std::vector<Vector2f> &texCoords,
			    std::vector<Vector3f> &normals,
			    std::vector<IndexedModel::Index> &indices,
			    std::vector<std::array<int, 4> > &boneIndices,
			    std::vector<std::array<float, 4> > &boneWeights)
{
	// Initialize bone data for each vertex
	boneIndices.resize(mesh->mNumVertices, { 0, 0, 0, 0 });
	boneWeights.resize(mesh->mNumVertices, { 0.0f, 0.0f, 0.0f, 0.0f });

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D pos = mesh->mVertices[i];
		aiVector3D norm = mesh->mNormals[i];
		aiVector3D texCoord = mesh->mTextureCoords[0][i];

		positions.push_back(Vector3f(pos.x, pos.y, pos.z));
		normals.push_back(Vector3f(norm.x, norm.y, norm.z));
		texCoords.push_back(Vector2f(texCoord.x, texCoord.y));
	}

	for (unsigned int i = 0; i < mesh->mNumBones; i++) {
		aiBone *bone = mesh->mBones[i];
		int boneID = i;
		for (unsigned int j = 0; j < bone->mNumWeights; j++) {
			aiVertexWeight weight = bone->mWeights[j];
			int vertexID = weight.mVertexId;

			for (int k = 0; k < 4; ++k) {
				if (boneWeights[vertexID][k] == 0.0f) {
					boneIndices[vertexID][k] = boneID;
					boneWeights[vertexID][k] =
						weight.mWeight;
					break;
				}
			}
		}
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			IndexedModel::Index index;
			index.vertex_index = face.mIndices[j];
			index.texCoord_index = index.vertex_index;
			index.normal_index = index.vertex_index;
			indices.push_back(index);
		}
	}
}

FBXModel::FBXModel(const std::string &file_path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(
		file_path, aiProcess_Triangulate | aiProcess_FlipUVs |
				   aiProcess_GenNormals);

	if (!scene || !scene->mRootNode) {
		throw std::runtime_error("Failed to load FBX file: " +
					 file_path);
	}

	process_node(scene->mRootNode, scene, positions, texCoords, normals,
		     bone_indices, bone_weights, indices);
	has_normals = !normals.empty();
	has_texCoords = !texCoords.empty();
}

IndexedModel FBXModel::to_indexed_model()
{
	IndexedModel model;
	std::unordered_map<IndexedModel::Index, int,
			   IndexedModel::Index::__hash__>
		model_index_map;

	for (int i = 0; i < indices.size(); i++) {
		IndexedModel::Index &current_index = indices[i];

		Vector3f position = positions[current_index.vertex_index];
		Vector2f texCoord;
		Vector3f normal;
		std::array<int, 4> boneIndex =
			bone_indices[current_index.vertex_index];
		std::array<float, 4> boneWeight =
			bone_weights[current_index.vertex_index];

		if (has_texCoords) {
			texCoord = texCoords[current_index.texCoord_index];
		}
		if (has_normals) {
			normal = normals[current_index.normal_index];
		}

		if (!model_index_map.count(current_index)) {
			model_index_map[current_index] = model.positions.size();
			model.positions.push_back(position);
			model.texCoords.push_back(texCoord);
			model.normals.push_back(normal);
			model.bone_indices.push_back(boneIndex);
			model.bone_weights.push_back(boneWeight);
		}

		model.indices.push_back(model_index_map[current_index]);
	}

	if (!has_normals) {
		model.calculate_normals();
	}

	return model;
}
