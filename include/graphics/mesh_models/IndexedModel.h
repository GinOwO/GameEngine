#pragma once

#include <math/Vector2f.h>
#include <math/Vector3f.h>

#include <vector>

struct IndexedModel {
	struct Index {
		int vertex_index;
		int texCoord_index;
		int normal_index;

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
				std::size_t h1 =
					std::hash<int>{}(index.vertex_index);
				std::size_t h2 =
					std::hash<int>{}(index.texCoord_index);
				std::size_t h3 =
					std::hash<int>{}(index.normal_index);

				return h1 ^ (h2 << 1) ^ (h3 << 1);
			}
		};
	};

	std::vector<Vector3f> positions;
	std::vector<Vector3f> normals;
	std::vector<Vector2f> texCoords;
	std::vector<int> indices;

	void calculate_normals()
	{
		for (int i = 0; i < indices.size(); i += 3) {
			int a = indices[i];
			int b = indices[i + 1];
			int c = indices[i + 2];

			Vector3f v1 = positions[b] - positions[a];
			Vector3f v2 = positions[c] - positions[a];

			Vector3f normal = v1.cross(v2).normalize();

			normals[a] = (normals[a] + normal).normalize();
			normals[b] = (normals[b] + normal).normalize();
			normals[c] = (normals[c] + normal).normalize();
		}
	}
};