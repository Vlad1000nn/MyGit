#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_norm;
layout (location = 2) in vec2 a_texture_coords;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

out vec3 norm;
out vec3 fragment_pos;
out vec2 texture_coords;

void main()
{
	fragment_pos = vec3(model * vec4(a_pos, 1.0f));
	gl_Position = proj * view * vec4(fragment_pos, 1.0f);
	norm = normalize(mat3(transpose(inverse(model))) * a_norm);
	texture_coords = a_texture_coords;
}
