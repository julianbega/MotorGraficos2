#version 330 core

in vec3 customColor;
in vec3 Normal;
in vec3 FragPos; 
in vec2 texCoord;

out vec4 fragColor;

struct Light {

    vec3 position;  
    vec3 direction;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
		
    float constant;
    float linear;
    float quadratic;
	
    float cutOff;
	float outerCutOff;
	bool enable;
	float constant;
};

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
uniform Light light;

vec3 result;
vec3 norm;
vec3 lightDir;
float diff;
vec3 viewDir;
vec3 reflectDir;
void main()
{	

	norm = normalize(Normal);
	
	//lightDir = normalize(lightPos - FragPos);
	lightDir = normalize(-light.direction);
	diff = max(dot(norm, lightDir), 0.0);	
	viewDir = normalize(viewPos - FragPos);
	reflectDir = reflect(-lightDir, norm);
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 
	if (type == 0)
	{
		vec3 ambient = ambientStrength * lightColor;

		vec3 diffuse = diff * lightColor;

		float specularStrength = 0.5;


		float spec = pow(max(dot(viewDir, reflectDir), 0.0), highlightStrength);
		vec3 specular = specularStrength * spec * lightColor;

		ambient  *= attenuation; 
		diffuse  *= attenuation;
		specular *= attenuation; 
		result = (ambient + diffuse + specular) * customColor;		
	}	
	else if (type == 1)
	{
		vec3 ambient = lightColor * material.ambient;

		vec3 diffuse = lightColor * (diff * material.diffuse);

		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = lightColor * (spec * material.specular);
		
		ambient  *= attenuation; 
		diffuse  *= attenuation;
		specular *= attenuation; 
		result = ambient + diffuse + specular;
		
	}
	else if (type == 2)
	{
	
	}	
	
		fragColor = vec4(result, 1.0);
}
