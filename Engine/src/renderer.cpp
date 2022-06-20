#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "renderer.h"

#include "gtc/type_ptr.hpp"


Renderer::Renderer() {
	
}

Renderer::~Renderer() {

}

void Renderer::createAtribPointers(unsigned int shaderAttribIndex, int dataAmmount, int dataSize, int dataPosition) {
	glVertexAttribPointer(shaderAttribIndex, dataAmmount, GL_FLOAT, GL_FALSE,sizeof(float) * dataSize, (void*)(sizeof(float) * dataPosition));
	glEnableVertexAttribArray(shaderAttribIndex);
}

void Renderer::setUVAttribPointer(unsigned int shaderID) {
    unsigned int posAttrib = glGetAttribLocation(shaderID, "pos");
    unsigned int colorAttrib = glGetAttribLocation(shaderID, "texColor");
    unsigned int texAttrib = glGetAttribLocation(shaderID, "aTexCoord");
    glUniform1i((glGetUniformLocation(shaderID, "ourTexture")), 0);
    createAtribPointers(posAttrib, 3, 9, 0);
    createAtribPointers(colorAttrib, 4, 9, 3);
    createAtribPointers(texAttrib, 2, 9, 7);
}


void Renderer::SetVertexAttributes(const char* name, int vertexSize, unsigned int shaderID) {
	unsigned int attribute = glGetAttribLocation(shaderID, name);
	createAtribPointers(attribute, 3, vertexSize, 0);
}
void Renderer::SetColorAttributes(const char* name, int vertexSize, unsigned int shaderID) {
	unsigned int attribute = glGetAttribLocation(shaderID, name);
	createAtribPointers(attribute, 3, vertexSize, 3);
}
void Renderer::SetNormalAttributes(const char* name, int vertexSize, unsigned int shaderID) {
	unsigned int attribute = glGetAttribLocation(shaderID, name);
	createAtribPointers(attribute, 3, vertexSize, 6);
}
void Renderer::SetTextureAttributes(const char* name, int vertexSize, unsigned int shaderID) {
	unsigned int attribute = glGetAttribLocation(shaderID, name);
	createAtribPointers(attribute, 2, vertexSize, 9);
}


void Renderer::startProgram(Shader& shader, glm::mat4 model) {
    unsigned int transformLoc = glGetUniformLocation(shader.getID(), "transform");
	shader.useProgram();
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void Renderer::generateVAO(unsigned int& vao) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void Renderer::bindVAO(unsigned int& vao) {
    glBindVertexArray(vao);
}

void Renderer::bindVBO(unsigned int& vbo, float* vertices, int verticesAmmount) {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * verticesAmmount, vertices, GL_STATIC_DRAW);
}

void Renderer::bindEBO(unsigned int& ebo, unsigned int* indices, int indicesAmmount) {
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * indicesAmmount, indices, GL_STATIC_DRAW);
}

void Renderer::bindAllBuffersAtOnce(unsigned int &vbo, unsigned int &vao, unsigned int& ebo, float *vertex, unsigned int *indices, int verticesAmmount, int indicesAmmount) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * verticesAmmount, vertex, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * indicesAmmount, indices, GL_STATIC_DRAW);
}

void Renderer::activateWireframeMode() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::deactivateWireframeMode() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::unbindBuffers(){
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void Renderer::deleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo) {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Renderer::draw(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmmount,glm::mat4 model, int vertexSize, int vertexIndex) {
    bindVAO(vao);
    bindVBO(vbo, vertices, verticesAmmount);
	shader.useProgram();

	glUniform1f(glGetUniformLocation(shader.getID(), "type"), 0.0f);
	glUniform1f(glGetUniformLocation(shader.getID(), "ambientStrength"), 0.3f);
	glUniform1f(glGetUniformLocation(shader.getID(), "highlightStrength"), 64.0f);
	glUniform3f(glGetUniformLocation(shader.getID(), "lightColor"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(shader.getID(), "lightPos"), 1.2f, 1.0f, 2.0f); 
	glUniform3f(glGetUniformLocation(shader.getID(), "viewPos"), 0.0f, 0.0f, 0.0f);
	SetVertexAttributes( "pos", vertexSize, shader.getID());
	SetColorAttributes("color", vertexSize, shader.getID());
	SetNormalAttributes("aNormal", vertexSize, shader.getID()); 
	
    startProgram(shader, model);
    glDrawElements(GL_TRIANGLES, vertexIndex, GL_UNSIGNED_INT, 0);
    unbindBuffers();
}

void Renderer::drawMaterial(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmmount, glm::mat4 model, int vertexSize, int vertexIndex) {
	bindVAO(vao);
	bindVBO(vbo, vertices, verticesAmmount);
	shader.useProgram(); 
	glUniform1f(glGetUniformLocation(shader.getID(), "type"), 1.0f);
	glUniform1f(glGetUniformLocation(shader.getID(), "ambientStrength"), 0.3f);
	glUniform1f(glGetUniformLocation(shader.getID(), "highlightStrength"), 64.0f);
	glUniform3f(glGetUniformLocation(shader.getID(), "lightColor"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(shader.getID(), "lightPos"), 1.2f, 1.0f, 2.0f);
	glUniform3f(glGetUniformLocation(shader.getID(), "viewPos"), 0.0f, 0.0f, 0.0f);


	glUniform3f(glGetUniformLocation(shader.getID(), "material.ambient"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(shader.getID(), "material.diffuse"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(shader.getID(), "material.specular"), 0.5f, 0.5f, 0.5f);
	glUniform1f(glGetUniformLocation(shader.getID(), "material.shininess"), 32.0f);
	SetVertexAttributes("pos", vertexSize, shader.getID());
	SetNormalAttributes("aNormal", vertexSize, shader.getID());

	startProgram(shader, model);
	glDrawElements(GL_TRIANGLES, vertexIndex, GL_UNSIGNED_INT, 0);
	unbindBuffers();
}

void Renderer::drawSprite(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmmount, glm::mat4 model){
    bindVAO(vao);
    bindVBO(vbo, vertices, verticesAmmount);
    setUVAttribPointer(shader.getID());
    startProgram(shader, model);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    unbindBuffers();
}
void Renderer::drawCamera(Shader& shader, glm::mat4 model, glm::mat4 view, glm::mat4 proj) {
    unsigned int transformLoc = glGetUniformLocation(shader.getID(), "transform");
    unsigned int viewLoc = glGetUniformLocation(shader.getID(), "view");
    unsigned int projLoc = glGetUniformLocation(shader.getID(), "proj");
    shader.useProgram();
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
}
