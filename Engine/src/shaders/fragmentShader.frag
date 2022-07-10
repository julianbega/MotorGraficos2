#version 460 core
out vec4 fragColor;

in vec3 FragPos;
in vec3 customColor;
in vec3 Normal;
in vec2 texCoord;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D ao;
	sampler2D normal;
	sampler2D roughness;
	float shininess;
};

struct DirectionalLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular; 
	bool enable;
};

struct PointLight {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;
	float constant;
	float linear;
	float quadratic;
	float cutoff;
	float outerCutOff;

	bool enable;
};

struct SpotLight{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;
	float constant;
	float linear;
	float quadratic;
	vec3 direction;
	float cutoff;
	float outerCutOff;

	bool enable;
};

uniform Material material;

uniform DirectionalLight directionalLight;
#define MAX_LIGHTS 4
uniform PointLight pointLight[MAX_LIGHTS];
uniform SpotLight spotLight[MAX_LIGHTS];


uniform vec3 viewPos;

uniform float specularStrength = 0.5f;

uniform sampler2D ourTexture;

vec3 CalculateDirectionalLight(DirectionalLight dL, vec3 norm, vec3 viewDir, float gamma);
vec3 CalculatePointLight(PointLight pL, vec3 norm, vec3 fragPos, vec3 viewDir, float gamma);
vec3 CalculateSpotLight(SpotLight sL, vec3 norm, vec3 fragPos, vec3 viewDir, float gamma);

void main(){
	
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	float gamma =2.2;

	vec3 result;

	result += CalculateDirectionalLight(directionalLight, norm, viewDir, gamma);

	for(int i = 0; i < MAX_LIGHTS; i++){
		result += CalculatePointLight(pointLight[i], norm, FragPos, viewDir, gamma);
		result += CalculateSpotLight(spotLight[i], norm, FragPos, viewDir, gamma);
	}
	result *= customColor;
	fragColor = vec4(pow(result, vec3(1.0/gamma)), 1.0);
}
vec3 CalculateDirectionalLight(DirectionalLight dL, vec3 norm, vec3 viewDir, float gamma){
	if(!dL.enable){
		return vec3(0);
	}

	vec3 lightDir = normalize(-dL.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 ambient =  dL.ambient * vec3(texture(material.diffuse, texCoord));
	vec3 diffuse = pow(vec3(dL.diffuse * diff * vec3(texture(material.diffuse, texCoord))),vec3(gamma));
	vec3 specular = dL.specular * spec * vec3(texture(material.specular, texCoord));

	return (ambient + diffuse + specular);

}
vec3 CalculatePointLight(PointLight pL, vec3 norm, vec3 fragPos, vec3 viewDir, float gamma){
	if(!pL.enable){
		return vec3(0);
	}

	vec3 lightDir = normalize(pL.position - fragPos);
    // diffuse shading
    float diff = max(dot(norm, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float lightDistance    = length(pL.position - fragPos);
    float attenuation = 1.0 / (pL.constant + pL.linear * lightDistance + 
  			     pL.quadratic * (lightDistance * lightDistance));    
    // combine results
    vec3 ambient  = pL.ambient  * vec3(texture(material.diffuse, texCoord));
    vec3 diffuse  = pow(vec3(pL.diffuse  * diff * vec3(texture(material.diffuse, texCoord))),vec3(gamma));
    vec3 specular = pL.specular * spec * vec3(texture(material.specular, texCoord));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
vec3 CalculateSpotLight(SpotLight sL, vec3 norm, vec3 fragPos, vec3 viewDir, float gamma){
	if(!sL.enable){
		return vec3(0);
	}

	vec3 lightDir = normalize(sL.position - fragPos);

	//ambient
	vec3 ambient =  sL.ambient * vec3(texture(material.diffuse, texCoord));
	//diffuse
	vec3 normals = normalize(norm);
	float diff = max(dot(normals, lightDir), 0.0);
	vec3 diffuse = pow(vec3(sL.diffuse * diff * vec3(texture(material.diffuse, texCoord))), vec3(gamma));
	//specular
	vec3 view= normalize(viewDir - fragPos);
	//vec3 reflectDir = reflect(-lightDir, normals);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(view, halfwayDir), 0.0), material.shininess);
	vec3 specular = sL.specular * spec * vec3(texture(material.specular, texCoord));

	//spotlight
	float theta = dot(lightDir, normalize(-sL.direction));
	float epsilon = sL.cutoff - sL.outerCutOff;
//	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	float intensity = smoothstep(0.0, 1.0, (theta - sL.outerCutOff) / epsilon);
	//ambient *= attenuation;
	diffuse *= intensity;
	specular *= intensity;

	float lightDistance = length(sL.position - fragPos); 
	float attenuation = 1.0 / (sL.constant + sL.linear * lightDistance + sL.quadratic * (lightDistance * lightDistance)); 
	
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}