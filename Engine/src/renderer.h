#ifndef RENDERER_H
#define RENDERER_H
#include "export.h"
#include "shader.h"
#include "mat4x4.hpp"
#include <vector>

class ENGINE_API Renderer {
public:
	Renderer();
	~Renderer();
	//							layout / index of attribute    ammount of data in a vertex (xyz = 3/ uv = 2)
	void createAtribPointers(unsigned int shaderAttribIndex, int dataAmmount, int dataSize, int dataPosition); //dataSize = amount of values in a vertex (xyz rgb uv...)
																							// dataPosition = position of the begining of data in vertex (xyz rgb -> r = 3 || xyz rgb -> x = 0) 
	void setPositionAttribPointer(unsigned int shaderID, const char* attribName);
	void setTintAttribPointer(unsigned int shaderID, const char* attribName);
	void setTexAttribPointer(unsigned int shaderID);
	void setCubeAttribPointer(Shader& shader);
	void setLightAttribPointer(Shader& shader);

	void startProgram(Shader &shader, glm::mat4 model);

	void generateVAO(unsigned int& vao);
	void generateVBO(unsigned int& vbo);
	void bindVAO(unsigned int& vao);
	void bindVBO(unsigned int& vbo, float* vertices, int verticesAmmount);
	void bindEBO(unsigned int& ebo, unsigned int* indices, int indicesAmmount);
	void bindAllBuffersAtOnce(unsigned int& vbo, unsigned int& vao, unsigned int& ebo, float* vertex, unsigned int* indices, int verticesAmmount, int indicesAmmount); // binds verteces to the vbo and vao

	void draw(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmmount, glm::mat4 model);
	void drawSprite(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmmount, glm::mat4 model);
	void drawCamera(Shader& shader, glm::mat4 model, glm::mat4 view, glm::mat4 proj);
	void drawCube(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmmount, glm::mat4 model);
	void drawMesh(Shader& shader, unsigned int& vao, unsigned int& vbo, glm::mat4& model, std::vector<unsigned int>& indices);
	void drawLight(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmount, glm::mat4 model);

	void activateWireframeMode();
	void deactivateWireframeMode();

	void unbindBuffers();
	void deleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo);
};
#endif // !RENDERER_H

