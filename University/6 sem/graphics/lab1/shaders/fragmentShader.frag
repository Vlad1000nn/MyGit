#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 view_pos;
uniform Material material;
uniform Light light;

in vec3 color;
in vec3 norm;
in vec3 fragment_pos;

out vec4 fragment_color;

void main()
{
	vec3 ambient = light.ambient * material.ambient;
  	
    vec3 light_dir = normalize(-light.direction);  
    float diff_value = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = light.diffuse * (diff_value * material.diffuse);
   
    vec3 view_dir = normalize(view_pos - fragment_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);  
    float spec_value = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec_value * material.specular);  
        
    vec3 result = (ambient + diffuse + specular) * color;
    fragment_color = vec4(result, 1.0);
}
