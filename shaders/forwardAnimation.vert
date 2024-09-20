#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in ivec4 inBoneIndices;
layout(location = 4) in vec4 inBoneWeights;

uniform mat4 MVP;
uniform mat4 model;
uniform mat4 boneMatrices[100]; // Assuming max 100 bones, adjust as needed

out vec2 texCoord;
out vec3 fragNormal;

void main()
{
	vec4 skinnedPosition = vec4(0.0);
	vec4 skinnedNormal = vec4(0.0);

	// Calculate skinned position and normal using bone data
	for (int i = 0; i < 4; ++i) {
		skinnedPosition += boneMatrices[inBoneIndices[i]] *
				   vec4(inPosition, 1.0) * inBoneWeights[i];
		skinnedNormal += boneMatrices[inBoneIndices[i]] *
				 vec4(inNormal, 0.0) * inBoneWeights[i];
	}

	gl_Position = MVP * skinnedPosition;
	texCoord = inTexCoord;
	fragNormal = mat3(transpose(inverse(model))) * skinnedNormal.xyz;
}
