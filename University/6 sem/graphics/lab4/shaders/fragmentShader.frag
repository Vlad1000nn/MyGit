#version 330 core

struct Material {
    sampler2D diffuse;
    vec3 specular;    
    float shininess;
}; 

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 color;
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};


uniform vec3 view_pos;
uniform Material material;
uniform DirectionalLight directional_light;
uniform SpotLight spot_light;
uniform sampler2D texture1;


in vec3 norm;
in vec3 fragment_pos;
in vec2 texture_coords;


out vec4 fragment_color;

vec3 calculate_directional_light(DirectionalLight light, vec3 normal, vec3 view_dir)
{

    vec3 light_dir = normalize(-light.direction);
 
    float diff_value = max(dot(normal, light_dir), 0.0f);

    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec_value = pow(max(dot(view_dir, reflect_dir), 0.0f), material.shininess);
 
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texture_coords));
    vec3 diffuse = light.diffuse * diff_value * vec3(texture(material.diffuse, texture_coords));
    vec3 specular = light.specular * (spec_value * material.specular);

    return vec3(ambient + diffuse + specular);
}

vec3 calculate_spot_light(SpotLight light, vec3 normal, vec3 fragment_pos, vec3 view_dir) 
{
    vec3 light_dir = normalize(light.position - fragment_pos);
	
    float diff_value = max(dot(normal, light_dir), 0.0);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec_value = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    float distance = length(light.position - fragment_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 
	
    float theta = dot(light_dir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texture_coords));
    vec3 diffuse = light.diffuse * diff_value * vec3(texture(material.diffuse, texture_coords));
    vec3 specular = light.specular * spec_value * material.specular;
    
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    
    return (ambient + diffuse + specular) * light.color;
}

void main()
{
    vec3 result = vec3(0.0f);
    vec3 view_dir = normalize(view_pos - fragment_pos);
    
    result += calculate_directional_light(directional_light, norm, view_dir);
    result += calculate_spot_light(spot_light, norm, fragment_pos, view_dir);

    fragment_color = vec4(result, 1.0f);
}
