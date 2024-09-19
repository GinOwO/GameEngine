#include <graphics/mesh_models/FBXModel.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>
#include <exception>
#include <stdexcept>

void FBXModel::process_node(aiNode *node, const aiScene *scene,
			    std::vector<Vector3f> &positions,
			    std::vector<Vector2f> &texCoords,
			    std::vector<Vector3f> &normals,
			    std::vector<IndexedModel::Index> &indices)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		process_mesh(mesh, scene, positions, texCoords, normals,
			     indices);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		process_node(node->mChildren[i], scene, positions, texCoords,
			     normals, indices);
	}
}

void FBXModel::process_mesh(aiMesh *mesh, const aiScene *scene,
			    std::vector<Vector3f> &positions,
			    std::vector<Vector2f> &texCoords,
			    std::vector<Vector3f> &normals,
			    std::vector<IndexedModel::Index> &indices)
{
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D pos = mesh->mVertices[i];
		aiVector3D norm = mesh->mNormals[i];
		aiVector3D texCoord = mesh->mTextureCoords[0][i];

		positions.push_back(Vector3f(pos.x, pos.y, pos.z));
		normals.push_back(Vector3f(norm.x, norm.y, norm.z));
		texCoords.push_back(Vector2f(texCoord.x, texCoord.y));
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			IndexedModel::Index index;
			index.vertex_index = face.mIndices[j];
			index.texCoord_index =
				index.vertex_index; // Assimp might not directly provide texCoord index
			index.normal_index =
				index.vertex_index; // Assimp might not directly provide normal index
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
		     indices);
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
		}

		model.indices.push_back(model_index_map[current_index]);
	}

	if (!has_normals) {
		model.calculate_normals();
	}

	return model;
}
