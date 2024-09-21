#include <graphics/mesh_models/OBJModel.h>

#include <math/Vector2f.h>
#include <math/Vector3f.h>

#include <graphics/mesh_models/IndexedModel.h>

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

IndexedModel::Index OBJModel::parse_obj_index(const std::string &token)
{
	std::string val;
	std::stringstream ss(token);
	std::vector<std::string> tokens;

	while (std::getline(ss, val, '/')) {
		tokens.push_back(val);
	}

	IndexedModel::Index result;
	result.vertex_index = std::stoi(tokens[0]) - 1;

	if (tokens.size() > 1) {
		has_texCoords = true;
		result.texCoord_index = std::stoi(tokens[1]) - 1;
		if (tokens.size() > 2) {
			has_normals = true;
			result.normal_index = std::stoi(tokens[2]) - 1;
		}
	}

	return result;
}

OBJModel::OBJModel(const std::string &file_path)
{
	std::ifstream file(file_path);
	has_normals = false;
	has_texCoords = false;
	std::string line, token;

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::vector<std::string> tokens;

		while (std::getline(ss, token, ' ')) {
			tokens.push_back(token);
		}

		if (tokens.size() == 0 || tokens[0] == "#")
			continue;

		if (tokens[0] == "v") {
			positions.push_back({ std::stof(tokens[1]),
					      std::stof(tokens[2]),
					      std::stof(tokens[3]) });
		} else if (tokens[0] == "vt") {
			texCoords.push_back(
				{ std::stof(tokens[1]), std::stof(tokens[2]) });
		} else if (tokens[0] == "vn") {
			normals.push_back({ std::stof(tokens[1]),
					    std::stof(tokens[2]),
					    std::stof(tokens[3]) });
		} else if (tokens[0] == "f") {
			for (int i = 0; i < tokens.size() - 3; i++) {
				indices.push_back(parse_obj_index(tokens[1]));
				indices.push_back(
					parse_obj_index(tokens[2 + i]));
				indices.push_back(
					parse_obj_index(tokens[3 + i]));
			}
		}
	}
}

IndexedModel OBJModel::to_indexed_model()
{
	IndexedModel model, normal_model;
	std::unordered_map<IndexedModel::Index, int,
			   IndexedModel::Index::__hash__>
		model_index_map;
	std::unordered_map<int, int> normal_index_map, index_map;

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

		if (!normal_index_map.count(current_index.vertex_index)) {
			normal_index_map[current_index.vertex_index] =
				normal_model.positions.size();
			normal_model.positions.push_back(position);
			normal_model.texCoords.push_back(texCoord);
			normal_model.normals.push_back(normal);
		}

		model.indices.push_back(model_index_map[current_index]);
		normal_model.indices.push_back(
			normal_index_map[current_index.vertex_index]);
		index_map[model_index_map[current_index]] =
			normal_index_map[current_index.vertex_index];
	}

	if (!has_normals) {
		normal_model.calculate_normals();

		for (int i = 0; i < model.positions.size(); i++) {
			model.normals[i] = normal_model.normals[index_map[i]];
		}
	}

	return model;
}