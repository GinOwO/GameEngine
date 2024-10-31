#pragma once

#include <math/Vector2f.h>
#include <math/Vector3f.h>

#include <vector>

struct IndexedModel {
	struct Index {
		int32_t vertex_index;
		int32_t texCoord_index;
		int32_t normal_index;

		constexpr bool
		operator==(const IndexedModel::Index &other) const noexcept
		{
			return vertex_index == other.vertex_index &&
			       texCoord_index == other.texCoord_index &&
			       normal_index == other.normal_index;
		}

		struct __hash__ {
			std::size_t operator()(
				const IndexedModel::Index &index) const noexcept
			{
				std::size_t h1 = std::hash<int32_t>{}(
					index.vertex_index);
				std::size_t h2 = std::hash<int32_t>{}(
					index.texCoord_index);
				std::size_t h3 = std::hash<int32_t>{}(
					index.normal_index);

				return h1 ^ (h2 << 1) ^ (h3 << 1);
			}
		};
	};

	std::vector<Vector3f> positions;
	std::vector<Vector3f> normals;
	std::vector<Vector2f> texCoords;
	std::vector<std::array<float, 4> > bone_weights;
	std::vector<std::array<int32_t, 4> > bone_indices;
	std::vector<int32_t> indices;

	void calculate_normals()
	{
		for (int32_t i = 0; i < indices.size(); i += 3) {
			int32_t a = indices[i];
			int32_t b = indices[i + 1];
			int32_t c = indices[i + 2];

			Vector3f v1 = positions[b] - positions[a];
			Vector3f v2 = positions[c] - positions[a];

			Vector3f normal = v1.cross(v2).normalize();

			normals[a] = (normals[a] + normal).normalize();
			normals[b] = (normals[b] + normal).normalize();
			normals[c] = (normals[c] + normal).normalize();
		}
	}
};