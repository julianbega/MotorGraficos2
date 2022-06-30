#ifndef RENDERER_H
#define RENDERER_H
#include "export.h"
#include "shader.h"
#include "mat4x4.hpp"
#include "global_declarations.h"

struct Material;

class ENGINE_API Renderer {
public:

	Renderer();
	~Renderer();
	//							layout / index of attribute    ammount of data in a vertex (xyz = 3/ uv = 2)
	void createAtribPointers(unsigned int shaderAttribIndex, int dataAmmount, int dataSize, int dataPosition); //dataSize = amount of values in a vertex (xyz rgb uv...)
							// dataPosition = position of the begining of data in vertex (xyz rgb -> r = 3 || xyz rgb -> x = 0) 
	void setUVAttribPointer(unsigned int shaderID);


	void SetVertexAttributes(const char* name, int vertexSize, unsigned int shaderID);
	void SetColorAttributes(const char* name, int vertexSize, unsigned int shaderID);
	void SetTextureAttributes(const char* name, int vertexSize, unsigned int shaderID);
	void SetNormalAttributes(const char* name, int vertexSize, unsigned int shaderID);


	void startProgram(Shader &shader, glm::mat4 model);

	void generateVAO(unsigned int& vao);
	void generateVBO(unsigned int& vbo);
	void bindVAO(unsigned int& vao);
	void bindVBO(unsigned int& vbo, float* vertices, int verticesAmmount);
	void bindEBO(unsigned int& ebo, unsigned int* indices, int indicesAmmount);
	void bindAllBuffersAtOnce(unsigned int& vbo, unsigned int& vao, unsigned int& ebo, float* vertex, unsigned int* indices, int verticesAmmount, int indicesAmmount); // binds verteces to the vbo and vao

	void draw(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmmount, glm::mat4 model, int vertexSize, int vertexIndex);
	void drawMaterial(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmmount, glm::mat4 model, int vertexSize, int vertexIndex);
	void drawCube(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmmount, glm::mat4 model);
	void drawSprite(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmmount, glm::mat4 model);
	void drawCamera(Shader& shader, glm::mat4 model, glm::mat4 view, glm::mat4 proj);

	void setCubeAttribPointer(Shader& shader);

	void activateWireframeMode();
	void deactivateWireframeMode();

	void unbindBuffers();
	void deleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo);
};
#endif // !RENDERER_H

