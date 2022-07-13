#include <GL/glew.h>
#include "lightSource.h"
#include "renderer.h"
#include "dataManager.h"
#include "texture_importer.h"
#include "shader.h"

#define MAX_LIGHTS 4

int LightSource::nextPointLightId = 0;
int LightSource::nextspotLightId = 0;

void LightSource::loadBaseSprite()
{
	float width = 0;
	float height = 0;
	if (_texImporter) {
		diffuse = _texImporter->loadTexture("../Engine/res/textures/BlankTexture.jpg" , width, height, false);
		specular = _texImporter->loadTexture("../Engine/res/textures/BlankTexture.jpg" , width, height, false);
	}
	else
		std::cout << "Couldn't find image" << std::endl;
}

void LightSource::bindBuffers()
{
	_renderer->generateVAO(_vao);
	_renderer->generateVBO(_vbo);
	_renderer->bindVAO(_vao);
	_renderer->bindVBO(_vbo, vertices, 264);
	_renderer->bindEBO(_ebo, indices, 36);
}

LightSource::LightSource(Renderer* renderer, Shader& shader, LightType type, std::string name) : Entity(renderer)
{
	_renderer = renderer;
	_type = type;
	_name = name;
	_shader = shader;
	_texImporter = new TextureImporter();
	_isLightSource = true;
	_entityShader = shader;
	isActive = false;
	_shader.setVec3("lightColor", _color);
	DataManager* data = DataManager::Get();
	data->addEntity(this, _id);
	switch (type)
	{
	case LightType::SpotLight:
		spotLightId = nextspotLightId++;
		break;
	case LightType::DirectionalLight:
		break;
	case LightType::PointLight:
		pointLightId = nextPointLightId++;
		break;
	default:
		break;
	}
}

LightSource::~LightSource()
{
	if (_texImporter){
		delete _texImporter;
		_texImporter = nullptr;
	}
}

void LightSource::init()
{
	loadBaseSprite();
	_renderer->setCubeAttribPointer(_shader);
	bindBuffers();
}

void LightSource::setColor(glm::vec3 color)
{
	_color = color;
	vertices[3] = color.x; vertices[4] = color.y; vertices[5] = color.z;
	vertices[14] = color.x; vertices[15] = color.y; vertices[16] = color.z;
	vertices[25] = color.x; vertices[26] = color.y; vertices[27] = color.z;
	vertices[36] = color.x; vertices[37] = color.y; vertices[38] = color.z;

	vertices[47] = color.x; vertices[48] = color.y; vertices[49] = color.z;
	vertices[58] = color.x; vertices[59] = color.y; vertices[60] = color.z;
	vertices[69] = color.x; vertices[70] = color.y; vertices[71] = color.z;
	vertices[80] = color.x; vertices[81] = color.y; vertices[82] = color.z;

	vertices[91] = color.x; vertices[92] = color.y; vertices[93] = color.z;
	vertices[102] = color.x; vertices[103] = color.y; vertices[104] = color.z;
	vertices[113] = color.x; vertices[114] = color.y; vertices[115] = color.z;
	vertices[124] = color.x; vertices[125] = color.y; vertices[126] = color.z;

	vertices[135] = color.x; vertices[136] = color.y; vertices[137] = color.z;
	vertices[146] = color.x; vertices[147] = color.y; vertices[148] = color.z;
	vertices[157] = color.x; vertices[158] = color.y; vertices[159] = color.z;
	vertices[168] = color.x; vertices[169] = color.y; vertices[170] = color.z;

	vertices[179] = color.x; vertices[180] = color.y; vertices[181] = color.z;
	vertices[190] = color.x; vertices[191] = color.y; vertices[192] = color.z;
	vertices[201] = color.x; vertices[202] = color.y; vertices[203] = color.z;
	vertices[212] = color.x; vertices[213] = color.y; vertices[214] = color.z;

	vertices[223] = color.x; vertices[224] = color.y; vertices[225] = color.z;
	vertices[234] = color.x; vertices[235] = color.y; vertices[236] = color.z;
	vertices[245] = color.x; vertices[246] = color.y; vertices[247] = color.z;
	vertices[256] = color.x; vertices[257] = color.y; vertices[258] = color.z;
}

void LightSource::setColor(float r, float g, float b)
{
	_color = glm::vec3(r, g, b);
	vertices[3] = r; vertices[4] = g; vertices[5] = b;
	vertices[14] = r; vertices[15] = g; vertices[16] = b;
	vertices[25] = r; vertices[26] = g; vertices[27] = b;
	vertices[36] = r; vertices[37] = g; vertices[38] = b;

	vertices[47] = r; vertices[48] = g; vertices[49] = b;
	vertices[58] = r; vertices[59] = g; vertices[60] = b;
	vertices[69] = r; vertices[70] = g; vertices[71] = b;
	vertices[80] = r; vertices[81] = g; vertices[82] = b;

	vertices[91] = r; vertices[92] = g; vertices[93] = b;
	vertices[102] = r; vertices[103] = g; vertices[104] = b;
	vertices[113] = r; vertices[114] = g; vertices[115] = b;
	vertices[124] = r; vertices[125] = g; vertices[126] = b;

	vertices[135] = r; vertices[136] = g; vertices[137] = b;
	vertices[146] = r; vertices[147] = g; vertices[148] = b;
	vertices[157] = r; vertices[158] = g; vertices[159] = b;
	vertices[168] = r; vertices[169] = g; vertices[170] = b;

	vertices[179] = r; vertices[180] = g; vertices[181] = b;
	vertices[190] = r; vertices[191] = g; vertices[192] = b;
	vertices[201] = r; vertices[202] = g; vertices[203] = b;
	vertices[212] = r; vertices[213] = g; vertices[214] = b;

	vertices[223] = r; vertices[224] = g; vertices[225] = b;
	vertices[234] = r; vertices[235] = g; vertices[236] = b;
	vertices[245] = r; vertices[246] = g; vertices[247] = b;
	vertices[256] = r; vertices[257] = g; vertices[258] = b;
}

void LightSource::draw()
{
	if (isActive) {
		switch (_type) {
		case LightType::DirectionalLight:
			_shader.setInt("directionalLight.enable", 0);

			break;
		case LightType::PointLight:
		{
			std::string id = std::to_string(pointLightId);
			std::string name = "pointLight[" + id + "].";
			_shader.setInt(std::string(name + "enable").c_str(), 0);
		}
		break;
		case LightType::SpotLight:
		{
			std::string id = std::to_string(pointLightId);
			std::string name = "spotLight[" + id + "].";
			_shader.setInt(std::string(name + "enable").c_str(), 0);
		}
		break;
		}
		return;
	}

	updateMatrices();
	updateVectors();
	switch (_type) {
	case LightType::DirectionalLight:
		_shader.setVec3("directionalLight.direction", transform.forward);
		_shader.setVec3("directionalLight.ambient", glm::vec3(.2f, .2f, .2f));
		_shader.setVec3("directionalLight.diffuse", _color);
		_shader.setVec3("directionalLight.specular", glm::vec3(1.0));
		_shader.setInt("directionalLight.enable", 1);

		break;
	case LightType::PointLight:
	{
		std::string id = std::to_string(pointLightId);
		std::string name = "pointLight[" + id + "].";
		_shader.setVec3(std::string(name + "position").c_str(), transform.position);
		_shader.setFloat(std::string(name + "cutoff").c_str(), glm::cos(glm::radians(12.5f)));
		_shader.setFloat(std::string(name + "outerCutOff").c_str(), glm::cos(glm::radians(17.5f)));

		_shader.setFloat(std::string(name + "constant").c_str(), 1.0f);
		_shader.setFloat(std::string(name + "linear").c_str(), 0.09f);
		_shader.setFloat(std::string(name + "quadratic").c_str(), 0.032f);

		_shader.setVec3(std::string(name + "ambient").c_str(), glm::vec3(.05f));
		_shader.setVec3(std::string(name + "diffuse").c_str(), _color);
		_shader.setVec3(std::string(name + "specular").c_str(), glm::vec3(1.0));

		_shader.setInt(std::string(name + "enable").c_str(), 1);
	}
	break;
	case LightType::SpotLight:
	{
		std::string id = std::to_string(pointLightId);
		std::string name = "spotLight[" + id + "].";
		_shader.setVec3(std::string(name + "position").c_str(), transform.position);
		_shader.setVec3(std::string(name + "direction").c_str(), transform.forward);
		_shader.setFloat(std::string(name + "cutoff").c_str(), glm::cos(glm::radians(12.5f)));
		_shader.setFloat(std::string(name + "outerCutOff").c_str(), glm::cos(glm::radians(17.5f)));

		_shader.setFloat(std::string(name + "constant").c_str(), 1.0f);
		_shader.setFloat(std::string(name + "linear").c_str(), 0.09f);
		_shader.setFloat(std::string(name + "quadratic").c_str(), 0.032f);

		_shader.setVec3(std::string(name + "ambient").c_str(), glm::vec3(0));
		_shader.setVec3(std::string(name + "diffuse").c_str(), _color);
		_shader.setVec3(std::string(name + "specular").c_str(), glm::vec3(1.0));

		_shader.setInt(std::string(name + "enable").c_str(), 1);
	}
	break;
	}


glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, diffuse);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, specular);
_renderer->drawCube(_shader, _vao, _vbo, vertices, 264, GetModel());
glDisable(GL_TEXTURE_2D);
}
