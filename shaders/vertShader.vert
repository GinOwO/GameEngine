#version 460 core
layout(location = 0) in vec3 position;

out vec3 color;

uniform float uniformTimerDelta;

void main()
{
	color = vec3(clamp(position * uniformTimerDelta, 0.0, 1.0));
	gl_Position = vec4(position, 1.0);
}
