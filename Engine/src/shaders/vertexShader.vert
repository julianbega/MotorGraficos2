#version 330 core

in vec3 pos;
in vec3 color;
in vec4 texColor;
in vec2 aTexCoord;
in vec3 aNormal;

out vec3 customColor;
out vec4 textureColor;
out vec2 texCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 proj;

void main() 
{
	customColor = color;
	textureColor = texColor;
	texCoord = aTexCoord;
	gl_Position = proj * view * transform * vec4(pos, 1.0);
	Normal = mat3(transpose(inverse(transform))) * aNormal;
    FragPos = vec3(transform * vec4(pos, 1.0));
}