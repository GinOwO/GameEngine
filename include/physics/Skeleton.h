#pragma once

#include <math/Matrix4f.h>

#include <assimp/scene.h>

#include <vector>
#include <string>
#include <unordered_map>

struct Bone {
	std::string name;
	Matrix4f offsetMatrix;
	Matrix4f finalTransformation;
};

class Skeleton {
    public:
	Skeleton(const aiScene *scene);

	std::unordered_map<std::string, int32_t> boneMapping;
	std::vector<Bone> bones;
	Matrix4f globalInverseTransform;

	void read_bones(const aiMesh *mesh);
	void update_bone_transform(float time, const aiNode *node,
				   const Matrix4f &parentTransform);

    private:
	const aiScene *scene;

	aiVector3D InterpolatePosition(float time, const aiNodeAnim *nodeAnim);
	aiQuaternion InterpolateRotation(float time,
					 const aiNodeAnim *nodeAnim);
	aiVector3D InterpolateScaling(float time, const aiNodeAnim *nodeAnim);
};
