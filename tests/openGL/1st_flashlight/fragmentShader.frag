#version 330 core

in vec3 Norm;
in vec3 FragPos;
out vec4 FragColor;

struct Material {
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

uniform Material material;

struct Light {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
		
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform Light light;

in vec2 texCoords;

uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;


void main()
{	
	//vec3 lightDir = normalize(-light.direction);
	vec3 lightDir = normalize(light.position - FragPos);
	
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

	float diff = max(dot(Norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));

	float specularPower = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, Norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords));

	vec3 emissionFactor = step(vec3(1.0f), vec3(1.0f) -  vec3(texture(material.specular, texCoords)));
	vec3 emission = emissionFactor *  vec3(texture(material.emission, texCoords));


	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);
	diffuse *= intensity;
	specular *= intensity;


	float distance = length(light.position - FragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	ambient *= attenuation;  
	diffuse *= attenuation;
	specular *= attenuation;   
	
	vec3 result = (ambient + diffuse + specular );	
	
	FragColor = vec4(result, 1.0f);
}