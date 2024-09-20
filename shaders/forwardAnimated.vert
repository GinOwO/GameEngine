#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoords;
layout(location = 3) in ivec4 inBoneIndices;
layout(location = 4) in vec4 inBoneWeights;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Assuming a maximum of 100 bones
const int MAX_BONES = 100;
uniform mat4 boneTransforms[MAX_BONES];

out vec2 texCoord0;
out vec3 normal0;
out vec3 worldPos0;

void main()
{
	mat4 boneTransform = mat4(0.0);
	boneTransform += boneTransforms[inBoneIndices[0]] * inBoneWeights[0];
	boneTransform += boneTransforms[inBoneIndices[1]] * inBoneWeights[1];
	boneTransform += boneTransforms[inBoneIndices[2]] * inBoneWeights[2];
	boneTransform += boneTransforms[inBoneIndices[3]] * inBoneWeights[3];

	vec4 worldPosition = model * boneTransform * vec4(inPosition, 1.0);
	gl_Position = projection * view * worldPosition;

	texCoord0 = inTexCoords;
	normal0 = mat3(transpose(inverse(model * boneTransform))) * inNormal;
	worldPos0 = worldPosition.xyz;
}
