#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 Norm;
out vec3 FragPos;
out vec2 texCoords;

void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0f));
	gl_Position = proj * view * vec4(FragPos, 1.0f);
	Norm = mat3(transpose(inverse(model))) * aNorm;
	texCoords = aTexCoords;
}