#include "shape.h"

#include <stdlib.h>

Shape::Shape(Type type, Renderer* renderer, Shader &shader, std::string shapeName) : Entity(renderer){
	shape = type;
	name = shapeName;
	_shader = shader;
	_vao = 0;
	_vbo = 0;
	_ebo = 0;
	DataManager* data = DataManager::Get();
	data->addEntity(this, id);
}
	
Shape::~Shape() {
	clearBuffers();
}

void Shape::initShape() {	
	generateVAO();
	bindVBO();
	bindEBO();
	setters();
}

void Shape::generateVAO() {
	_renderer->generateVAO(_vao);
}

void Shape::bindVAO() {
	_renderer->bindVAO(_vao);
}

void Shape::setters() {
	switch (shape)
	{
	case Type::quad:
		_renderer->SetVertexAttributes("pos", 6, _shader.getID());
		_renderer->SetColorAttributes("texColor", 6, _shader.getID());
		break;
	case Type::tri:
		_renderer->SetVertexAttributes("pos", 6, _shader.getID());
		_renderer->SetColorAttributes("texColor", 6, _shader.getID());
		break;
	case Type::cube:
		_renderer->SetVertexAttributes("pos", 6, _shader.getID());
		_renderer->SetColorAttributes("texColor", 6, _shader.getID());
		break;
	case Type::normalCube:
		_renderer->SetVertexAttributes("pos", 9, _shader.getID());
		_renderer->SetColorAttributes("texColor", 9, _shader.getID());
		_renderer->SetNormalAttributes("aNormal", 9, _shader.getID());
		//_renderer->SetTextureAttributes("aTexCoord", 9, _shader.getID());
		break;
	default:
		break;
	}
}

void Shape::bindVBO() {
	switch (shape)
	{
	case Type::quad:
		_renderer->bindVBO(_vbo, quadVertices, 28);
		break;
	case Type::tri:
		_renderer->bindVBO(_vbo, triangleVertices, 22);
		break;
	case Type::cube:
		_renderer->bindVBO(_vbo, cubeVertices, 52);
		break; 
	case Type::normalCube:
		_renderer->bindVBO(_vbo, cubeVertices, 328);
		break;
	default:
		break;
	}
}

void Shape::bindEBO() {
	switch (shape)
	{
	case Type::quad:
		_renderer->bindEBO(_ebo, quadIndices, 6);
		break;
	case Type::tri:
		_renderer->bindEBO(_ebo, triangleIndices, 3);
		break;
	case Type::cube:
		_renderer->bindEBO(_ebo, cubeIndices, 36);
		break;
	case Type::normalCube:
		_renderer->bindEBO(_ebo, cubeIndicesNormal, 36);
		break;
	default:
		break;
	}
}

void Shape::bindBuffers(float* quadVertex, float* triVertex, int quadVertexSize, int triVertexSize){
	generateVAO();
	switch (shape)
	{
	case Type::quad:
		_renderer->bindVBO(_vbo, quadVertex, quadVertexSize);
		_renderer->bindEBO(_ebo, quadIndices, 6);
		break;
	case Type::tri:
		_renderer->bindVBO(_vbo, triVertex, triVertexSize);
		_renderer->bindEBO(_ebo, triangleIndices, 3);
		break;
	case Type::cube:
		_renderer->bindVBO(_vbo, cubeVertices, 52);
		_renderer->bindEBO(_ebo, cubeIndices, 26);
		break;
	case Type::normalCube:
		_renderer->bindVBO(_vbo, cubeVertices, 328);
		_renderer->bindEBO(_ebo, cubeIndicesNormal, 36);
		break;
	default:
		break;
	}
}

void Shape::setColor(float r, float g, float b) {
	parameterType = 0;
	switch (shape)
	{
	case Type::quad:
		quadVertices[3] = r; quadVertices[4] = g; quadVertices[5] = b;
		quadVertices[9] = r; quadVertices[10] = g; quadVertices[11] = b;
		quadVertices[15] = r; quadVertices[16] = g; quadVertices[17] = b;
		quadVertices[21] = r; quadVertices[22] = g; quadVertices[23] = b;
		break;
	case Type::tri:
		triangleVertices[3] = r; triangleVertices[4] = g; triangleVertices[5] = b;
		triangleVertices[9] = r; triangleVertices[10] = g; triangleVertices[11] = b;
		triangleVertices[15] = r; triangleVertices[16] = g; triangleVertices[17] = b;
		break;
	case Type::cube:
		cubeVertices[3] = r; cubeVertices[4] = g; cubeVertices[5] = b;
		cubeVertices[9] = r; cubeVertices[10] = g; cubeVertices[11] = b;
		cubeVertices[15] = r; cubeVertices[16] = g; cubeVertices[17] = b;
		cubeVertices[21] = r; cubeVertices[22] = g; cubeVertices[23] = b;
		break;	
	default:
		break;
	}
}

void Shape::clearBuffers() {
	_renderer->deleteBuffers(_vao, _vbo, _ebo);
}
/*
void Shape::setMaterial(vec3 ambient, vec3 diffuse, vec3 specular, float shininess)
{
	parameterType = 1;
	_material.ambient = ambient;
	_material.diffuse = diffuse;
	_material.specular = specular;
	_material.shininess = shininess;
}

void Shape::setMaterial(Material mat)
{
	parameterType = 1;
	_material.ambient = mat.ambient;
	_material.diffuse = mat.diffuse;
	_material.specular = mat.specular;
	_material.shininess = mat.shininess;
}
*/
void Shape::draw() {
	updateMatrices();
	if (parameterType == 0)
	{
		switch (shape)
		{
		case Type::quad:
			_renderer->draw(_shader, _vao, _vbo, quadVertices, 28, GetModel(), 6, 6);
			break; 
		case Type::tri:
			_renderer->draw(_shader, _vao, _vbo, triangleVertices, 22, GetModel(), 6, 3);
			break;
		case Type::cube:
			_renderer->draw(_shader, _vao, _vbo, cubeVertices, 52, GetModel(), 6, 36);
			break;
		case Type::normalCube:
			_renderer->draw(_shader, _vao, _vbo, cubeVerticesNormal, 328, GetModel(), 9, 36);
			break;
		default:
			break;
		}
	}
	else if (parameterType == 1)
	{
		switch (shape)
		{
		case Type::quad:
			_renderer->drawMaterial(_shader, _vao, _vbo, quadVertices, 28, GetModel(), 6, 6);
			break;
		case Type::tri:
			_renderer->drawMaterial(_shader, _vao, _vbo, triangleVertices, 22, GetModel(), 6, 3);
			break;
		case Type::cube:
			_renderer->drawMaterial(_shader, _vao, _vbo, cubeVertices, 52, GetModel(), 6, 36);
			break;
		case Type::normalCube:
			_renderer->drawMaterial(_shader, _vao, _vbo, cubeVerticesNormal, 328, GetModel(), 9, 36);
			break;
		default:
			break;
		}
	}
}

