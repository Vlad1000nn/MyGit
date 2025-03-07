#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexPos;

out vec3 ourColor;
out vec2 texPos;

uniform mat4 trans;

void main()
{
	gl_Position = trans * vec4(aPos, 1.0);
	ourColor = aColor;
	texPos = aTexPos;
}