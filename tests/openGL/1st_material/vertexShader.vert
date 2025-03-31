#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 Norm;
out vec3 FragPos;

void main()
{
	// Calculate global pos of fragment(bcs we set up light there)
	FragPos = vec3(model * vec4(aPos, 1.0f));
	gl_Position = proj * view * vec4(FragPos, 1.0f);
	// using Normal matrix( do not recommend do it inside shader)
	Norm = mat3(transpose(inverse(model))) * aNorm;
}