#pragma once

#include <math/Vector2f.h>
#include <math/Vector3f.h>

#include <vector>

struct IndexedModel {
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