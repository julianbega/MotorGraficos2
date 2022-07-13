#include "mesh.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace Engine;

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Shader shader) : Entity(_renderer) {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	_shader = shader;

	SetUpMesh();
}

Mesh::~Mesh() {

}

void Mesh::SetUpMesh() {
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//Especificar al shader las posiciones, las normales y las uv del mesh
	_positionAttrib = glGetAttribLocation(_shader.getID(), "inPosition");
	glVertexAttribPointer(_positionAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(_positionAttrib);

	_normalAttrib = glGetAttribLocation(_shader.getID(), "inNormal");
	glVertexAttribPointer(_normalAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(_normalAttrib);

	_textureAttrib =  glGetAttribLocation(_shader.getID(), "inTexCoord");
	glVertexAttribPointer(_textureAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(_textureAttrib);

	glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader, glm::mat4 mvp) {
	updateMatrices();
	updateModel();
	//Pasar este codigo a renderer y que reciba como parametros todos los datos necesarios
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
		std::string name = textures[i].type;
		if (name == "diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "specular")
			number = std::to_string(specularNr++);
	
		glUniform1f(glGetUniformLocation(shader.getID(), ("material." + name).c_str()), i);
		//glUniform1f(glGetUniformLocation(shader.GetID(), (name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	shader.useProgram();
	shader.setMat4("transform", mvp ); // si no funca chequear que lo mande al vertex en lugar del fragment

	_positionAttrib = glGetAttribLocation(shader.getID(), "inPosition");
	glVertexAttribPointer(_positionAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(_positionAttrib);

	_normalAttrib = glGetAttribLocation(shader.getID(), "inNormal");
	glVertexAttribPointer(_normalAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(_normalAttrib);

	_textureAttrib = glGetAttribLocation(shader.getID(), "inTexCoord");
	glVertexAttribPointer(_textureAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(_textureAttrib);

	_colorAttrib = glGetAttribLocation(shader.getID(), "inColor");
	glVertexAttribPointer(_colorAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
	glEnableVertexAttribArray(_colorAttrib);

	glBindTexture(GL_TEXTURE_2D, 0);


	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}