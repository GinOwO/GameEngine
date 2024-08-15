#version 460 core

in vec3 color;

out vec4 finalColor;

void main()
{
	finalColor = vec4(color, 1.0);
}
