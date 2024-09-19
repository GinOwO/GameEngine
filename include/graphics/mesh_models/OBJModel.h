#pragma once

// TODO: comments

#include <math/Vector2f.h>
#include <math/Vector3f.h>

#include <graphics/mesh_models/IndexedModel.h>

#include <vector>
#include <string>
#include <fstream>

struct OBJIndex {
	int vertex_index;
	int texCoord_index;
	int normal_index;

	constexpr bool operator==(const OBJIndex &other) const noexcept
	{
		return vertex_index == other.vertex_index &&
		       texCoord_index == other.texCoord_index &&
		       normal_index == other.normal_index;
	}

	struct __hash__ {
		std::size_t operator()(const OBJIndex &index) const noexcept
		{
			std::size_t h1 = std::hash<int>{}(index.vertex_index);
			std::size_t h2 = std::hash<int>{}(index.texCoord_index);
			std::size_t h3 = std::hash<int>{}(index.normal_index);

			return h1 ^ (h2 << 1) ^ (h3 << 1);
		}
	};
};

class OBJModel {
	OBJIndex parse_obj_index(const std::string &token);

    public:
	std::vector<Vector3f> positions;
	std::vector<Vector3f> normals;
	std::vector<Vector2f> texCoords;
	std::vector<OBJIndex> indices;
	bool has_normals;
	bool has_texCoords;

	OBJModel(std::ifstream &file);
	IndexedModel to_indexed_model();
};