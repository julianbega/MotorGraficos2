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

uniform vec3 lightColor;
uniform float ambientStrength;
uniform vec3 lightPos;  
uniform vec3 viewPos;
uniform float highlightStrength;
uniform Material material;


uniform float type;
vec3 result;
vec3 norm;
vec3 lightDir;
float diff;
vec3 viewDir;
vec3 reflectDir;
void main()
{	

	norm = normalize(Normal);
	
	lightDir = normalize(lightPos - FragPos);
	diff = max(dot(norm, lightDir), 0.0);
	
	viewDir = normalize(viewPos - FragPos);
	reflectDir = reflect(-lightDir, norm);
	if (type == 0)
	{
		vec3 ambient = ambientStrength * lightColor;

		vec3 diffuse = diff * lightColor;

		float specularStrength = 0.5;


		float spec = pow(max(dot(viewDir, reflectDir), 0.0), highlightStrength);
		vec3 specular = specularStrength * spec * lightColor;

		result = (ambient + diffuse + specular) * customColor;		
	}	
	else if (type == 1)
	{
		vec3 ambient = lightColor * material.ambient;

		vec3 diffuse = lightColor * (diff * material.diffuse);

		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = lightColor * (spec * material.specular);

		result = ambient + diffuse + specular;
		
	}
	else if (type == 2)
	{
	
	}	
	
		fragColor = vec4(result, 1.0);
}
