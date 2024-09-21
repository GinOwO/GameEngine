#version 330 core

in vec2 texCoord;
in vec3 fragNormal;

uniform sampler2D diffuseTexture;
uniform vec3 ambientIntensity;

out vec4 fragColor;

void main()
{
	vec3 texColor = texture(diffuseTexture, texCoord).rgb;
	vec3 ambient = texColor * ambientIntensity;
	vec3 normal = normalize(fragNormal);

	fragColor = vec4(ambient * texColor, 1.0);
}
