#version 330 core
in vec3 ourColor;
in vec2 texPos;
out vec4 FragColor;
uniform sampler2D texture1;
uniform sampler2D texture2;
void main()
{
	FragColor = mix(texture(texture1, texPos), texture(texture2, texPos), 0.5);
}