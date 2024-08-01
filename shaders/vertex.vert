#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 fragCoord;

uniform vec2 iResolution;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	fragCoord = aTexCoord * iResolution;
}