#version 460 core

in vec2 texCoord0;

uniform vec3 ambient_intensity;
uniform sampler2D sampler;

out vec4 finalColor;

void main()
{
	finalColor =
		texture(sampler, texCoord0.xy) * vec4(ambient_intensity, 1.);
}
