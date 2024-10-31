#include <physics/Skeleton.h>

#include <math/Matrix4f.h>
#include <math/Quaternion.h>

#include <assimp/scene.h>
#include <assimp/anim.h>

Matrix4f from_aiMatrix4x4(const aiMatrix4x4 &am)
{
	float m[4][4];
	for (int32_t i = 0; i < 4; i++) {
		for (int32_t j = 0; j < 4; j++) {
			m[i][j] = am[i][j];
		}
	}
	return Matrix4f(m);
}

inline constexpr float determinant(float **m)
{
	return m[0][3] * m[1][2] * m[2][1] * m[3][0] -
	       m[0][2] * m[1][3] * m[2][1] * m[3][0] -
	       m[0][3] * m[1][1] * m[2][2] * m[3][0] +
	       m[0][1] * m[1][3] * m[2][2] * m[3][0] +
	       m[0][2] * m[1][1] * m[2][3] * m[3][0] -
	       m[0][1] * m[1][2] * m[2][3] * m[3][0] -
	       m[0][3] * m[1][2] * m[2][0] * m[3][1] +
	       m[0][2] * m[1][3] * m[2][0] * m[3][1] +
	       m[0][3] * m[1][0] * m[2][2] * m[3][1] -
	       m[0][0] * m[1][3] * m[2][2] * m[3][1] -
	       m[0][2] * m[1][0] * m[2][3] * m[3][1] +
	       m[0][0] * m[1][2] * m[2][3] * m[3][1] +
	       m[0][3] * m[1][1] * m[2][0] * m[3][2] -
	       m[0][1] * m[1][3] * m[2][0] * m[3][2] -
	       m[0][3] * m[1][0] * m[2][1] * m[3][2] +
	       m[0][0] * m[1][3] * m[2][1] * m[3][2] +
	       m[0][1] * m[1][0] * m[2][3] * m[3][2] -
	       m[0][0] * m[1][1] * m[2][3] * m[3][2] -
	       m[0][2] * m[1][1] * m[2][0] * m[3][3] +
	       m[0][1] * m[1][2] * m[2][0] * m[3][3] +
	       m[0][2] * m[1][0] * m[2][1] * m[3][3] -
	       m[0][0] * m[1][2] * m[2][1] * m[3][3] -
	       m[0][1] * m[1][0] * m[2][2] * m[3][3] +
	       m[0][0] * m[1][1] * m[2][2] * m[3][3];
}

void cofactor(float **m, float **temp, int32_t p, int32_t q, int32_t n)
{
	int32_t i = 0, j = 0;
	for (int32_t row = 0; row < n; row++) {
		for (int32_t col = 0; col < n; col++) {
			if (row != p && col != q) {
				temp[i][j++] = m[row][col];
				if (j == n - 1) {
					j = 0;
					i++;
				}
			}
		}
	}
}

// Function to compute the adjugate of a matrix
void adjugate(float **m, float adj[4][4])
{
	float temp[4][4];
	int32_t sign = 1;
	for (int32_t i = 0; i < 4; i++) {
		for (int32_t j = 0; j < 4; j++) {
			cofactor(m, (float **)((void *)temp), i, j, 4);
			sign = ((i + j) % 2 == 0) ? 1 : -1;
			adj[j][i] =
				sign * determinant((float **)((void *)temp));
		}
	}
}

Matrix4f inverse(const Matrix4f &mat)
{
	float **m = (float **)((void *)mat.get_matrix());
	float inv[4][4];
	float det = determinant(m);
	if (det == 0) {
		return Matrix4f::Identity_Matrix();
	}

	float adj[4][4];
	adjugate(m, adj);

	for (int32_t i = 0; i < 4; i++) {
		for (int32_t j = 0; j < 4; j++) {
			inv[i][j] = adj[i][j] / det;
		}
	}

	return Matrix4f(inv);
}

Skeleton::Skeleton(const aiScene *scene)
	: scene(scene)
{
	globalInverseTransform =
		inverse(from_aiMatrix4x4(scene->mRootNode->mTransformation));
}

void Skeleton::read_bones(const aiMesh *mesh)
{
	bones.resize(mesh->mNumBones);
	for (uint32_t i = 0; i < mesh->mNumBones; i++) {
		aiBone *bone = mesh->mBones[i];
		std::string boneName = bone->mName.data;
		boneMapping[boneName] = i;

		bones[i].name = boneName;
		bones[i].offsetMatrix = from_aiMatrix4x4(bone->mOffsetMatrix);
	}
}

void Skeleton::update_bone_transform(float time, const aiNode *node,
				     const Matrix4f &parentTransform)
{
	std::string nodeName(node->mName.data);
	Matrix4f nodeTransformation = from_aiMatrix4x4(node->mTransformation);

	const aiAnimation *animation =
		scene->mAnimations[0]; // Assume first animation

	// Retrieve the bone's transformation based on the animation data
	const aiNodeAnim *nodeAnim = nullptr;
	for (uint32_t i = 0; i < animation->mNumChannels; i++) {
		if (std::string(animation->mChannels[i]->mNodeName.data) ==
		    nodeName) {
			nodeAnim = animation->mChannels[i];
			break;
		}
	}

	if (nodeAnim) {
		// Interpolate scaling
		aiVector3D scaling;
		aiQuaternion rotation;
		aiVector3D translation;

		// Compute transformations (implement Interpolate functions)
		translation = InterpolatePosition(time, nodeAnim);
		rotation = InterpolateRotation(time, nodeAnim);
		scaling = InterpolateScaling(time, nodeAnim);

		Matrix4f scalingMatrix =
			Matrix4f::Scale_Matrix(scaling.x, scaling.y, scaling.z);
		Matrix4f rotationMatrix = Quaternion(rotation.x, rotation.w,
						     rotation.z, rotation.w)
						  .to_rotation_matrix();
		Matrix4f translationMatrix = Matrix4f::Translation_Matrix(
			translation.x, translation.y, translation.z);

		nodeTransformation =
			translationMatrix * rotationMatrix * scalingMatrix;
	}

	Matrix4f globalTransformation = parentTransform * nodeTransformation;

	if (boneMapping.find(nodeName) != boneMapping.end()) {
		int32_t boneIndex = boneMapping[nodeName];
		bones[boneIndex].finalTransformation =
			globalInverseTransform * globalTransformation *
			bones[boneIndex].offsetMatrix;
	}

	for (uint32_t i = 0; i < node->mNumChildren; i++) {
		update_bone_transform(time, node->mChildren[i],
				      globalTransformation);
	}
}

int32_t FindPositionKey(float time, const aiNodeAnim *nodeAnim)
{
	for (int32_t i = 0; i < nodeAnim->mNumPositionKeys - 1; ++i) {
		if (time < nodeAnim->mPositionKeys[i + 1].mTime) {
			return i;
		}
	}
	return 0;
}

int32_t FindRotationKey(float time, const aiNodeAnim *nodeAnim)
{
	for (int32_t i = 0; i < nodeAnim->mNumRotationKeys - 1; ++i) {
		if (time < nodeAnim->mRotationKeys[i + 1].mTime) {
			return i;
		}
	}
	return 0;
}

int32_t FindScalingKey(float time, const aiNodeAnim *nodeAnim)
{
	for (int32_t i = 0; i < nodeAnim->mNumScalingKeys - 1; ++i) {
		if (time < nodeAnim->mScalingKeys[i + 1].mTime) {
			return i;
		}
	}
	return 0;
}

float InterpolateValue(float a, float b, float factor)
{
	return a + (b - a) * factor;
}

aiVector3D Skeleton::InterpolatePosition(float time, const aiNodeAnim *nodeAnim)
{
	if (nodeAnim->mNumPositionKeys == 1) {
		return nodeAnim->mPositionKeys[0].mValue;
	}

	// Find position keyframes surrounding the current time
	int32_t positionIndex = FindPositionKey(time, nodeAnim);
	int32_t nextPositionIndex =
		(positionIndex + 1) % nodeAnim->mNumPositionKeys;

	// Get the position keys
	const aiVectorKey &positionKey = nodeAnim->mPositionKeys[positionIndex];
	const aiVectorKey &nextPositionKey =
		nodeAnim->mPositionKeys[nextPositionIndex];

	// Calculate interpolation factor
	float deltaTime = nextPositionKey.mTime - positionKey.mTime;
	float factor = (time - positionKey.mTime) / deltaTime;

	// Interpolate position
	aiVector3D interpolatedPosition;
	interpolatedPosition.x = InterpolateValue(
		positionKey.mValue.x, nextPositionKey.mValue.x, factor);
	interpolatedPosition.y = InterpolateValue(
		positionKey.mValue.y, nextPositionKey.mValue.y, factor);
	interpolatedPosition.z = InterpolateValue(
		positionKey.mValue.z, nextPositionKey.mValue.z, factor);

	return interpolatedPosition;
}

aiQuaternion Skeleton::InterpolateRotation(float time,
					   const aiNodeAnim *nodeAnim)
{
	if (nodeAnim->mNumRotationKeys == 1) {
		return nodeAnim->mRotationKeys[0].mValue;
	}

	// Find rotation keyframes surrounding the current time
	int32_t rotationIndex = FindRotationKey(time, nodeAnim);
	int32_t nextRotationIndex =
		(rotationIndex + 1) % nodeAnim->mNumRotationKeys;

	// Get the rotation keys
	const aiQuatKey &rotationKey = nodeAnim->mRotationKeys[rotationIndex];
	const aiQuatKey &nextRotationKey =
		nodeAnim->mRotationKeys[nextRotationIndex];

	// Calculate interpolation factor
	float deltaTime = nextRotationKey.mTime - rotationKey.mTime;
	float factor = (time - rotationKey.mTime) / deltaTime;

	// Interpolate rotation using spherical linear interpolation (slerp)
	aiQuaternion interpolatedRotation;
	aiQuaternion::Interpolate(interpolatedRotation, rotationKey.mValue,
				  nextRotationKey.mValue, factor);

	// Normalize interpolated quaternion
	interpolatedRotation.Normalize();

	return interpolatedRotation;
}

aiVector3D Skeleton::InterpolateScaling(float time, const aiNodeAnim *nodeAnim)
{
	if (nodeAnim->mNumScalingKeys == 1) {
		return nodeAnim->mScalingKeys[0].mValue;
	}

	// Find scaling keyframes surrounding the current time
	int32_t scalingIndex = FindScalingKey(time, nodeAnim);
	int32_t nextScalingIndex =
		(scalingIndex + 1) % nodeAnim->mNumScalingKeys;

	// Get the scaling keys
	const aiVectorKey &scalingKey = nodeAnim->mScalingKeys[scalingIndex];
	const aiVectorKey &nextScalingKey =
		nodeAnim->mScalingKeys[nextScalingIndex];

	// Calculate interpolation factor
	float deltaTime = nextScalingKey.mTime - scalingKey.mTime;
	float factor = (time - scalingKey.mTime) / deltaTime;

	// Interpolate scaling
	aiVector3D interpolatedScaling;
	interpolatedScaling.x = InterpolateValue(
		scalingKey.mValue.x, nextScalingKey.mValue.x, factor);
	interpolatedScaling.y = InterpolateValue(
		scalingKey.mValue.y, nextScalingKey.mValue.y, factor);
	interpolatedScaling.z = InterpolateValue(
		scalingKey.mValue.z, nextScalingKey.mValue.z, factor);

	return interpolatedScaling;
}
