#pragma once

// TODO: comments

#include <math/Vector2f.h>
#include <math/Vector3f.h>

#include <graphics/mesh_models/IndexedModel.h>

#include <vector>
#include <string>
#include <fstream>

class OBJModel {
	IndexedModel::Index parse_obj_index(const std::string &token);

    public:
	std::vector<Vector3f> positions;
	std::vector<Vector3f> normals;
	std::vector<Vector2f> texCoords;
	std::vector<IndexedModel::Index> indices;
	bool has_normals;
	bool has_texCoords;

	OBJModel(const std::string &file_path);
	IndexedModel to_indexed_model();
};