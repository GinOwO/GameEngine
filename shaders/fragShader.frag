#version 460 core

in vec2 texCoord0;

uniform vec3 color;
uniform sampler2D sampler;

out vec4 finalColor;

void main()
{
	vec4 texColor = texture(sampler, texCoord0.xy);
	if (texColor == vec4(0)) {
		finalColor = vec4(color, 1.);
	} else {
		finalColor = texColor * vec4(color, 1.);
	}
}
