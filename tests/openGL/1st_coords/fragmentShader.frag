#version 330 core
in vec2 texPos;
out vec4 FragColor;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixVal;

void main()
{
	FragColor = mix(texture(texture1, texPos), texture(texture2, vec2(1.0 - texPos.x, texPos.y)), mixVal);
}