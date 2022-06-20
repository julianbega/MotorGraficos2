#version 330 core

in vec3 customColor;
in vec3 Normal;
in vec3 FragPos; 

out vec4 fragColor;


struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambientStrength;
uniform vec3 lightPos;  
uniform vec3 viewPos;
uniform float highlightStrength;
uniform Material material;

void main()
{	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  

    vec3 ambient = ambientStrength * lightColor;

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), highlightStrength);
	vec3 specular = specularStrength * spec * lightColor;  

	vec3 result = (ambient+ diffuse + specular) * customColor;
	fragColor = vec4(result,1.0f);
}
