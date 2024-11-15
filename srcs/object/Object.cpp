#include "Object.hpp"
#include "ShaderManager.hpp"
#include "glad.h"
#include <cstdlib>
#include <iostream>

Object::Object(std::vector<glm::vec3> vertices, std::vector<glm::uvec3> indices, ShaderManager shaderManager)
{
	_objectId = std::rand();
	_vertices = vertices;
	_indices = indices;
	_shaderManager = shaderManager;

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(_vertices[0]), _vertices.data(), GL_STATIC_DRAW);

	for(auto vert : _vertices)
		std::cout << vert.x << " " << vert.y << " " << vert.z << std::endl;
	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(_indices[0]), _indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Object::Object(std::vector<glm::vec3> vertices, std::vector<glm::uvec3> indices, ShaderManager shaderManager, glm::vec3 pos)
{
	_objectId = std::rand();
	_vertices = vertices;
	_indices = indices;
	_shaderManager = shaderManager;
	_position = pos;

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(_vertices[0]), _vertices.data(), GL_STATIC_DRAW);

	for(auto vert : _vertices)
		std::cout << vert.x << " " << vert.y << " " << vert.z << std::endl;
	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(_indices[0]), _indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Object::~Object() {}

unsigned int Object::getVao() const { return (_vao); }

std::vector<glm::uvec3> Object::getIndices() const { return (_indices); }

ShaderManager Object::getShaderManager() const { return (_shaderManager); }

glm::vec3 Object::getPosition() const { return _position; }

void Object::setPosition(glm::vec3 pos) { _position = pos; }
