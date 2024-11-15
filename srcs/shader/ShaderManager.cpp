#include "ShaderManager.hpp"
#include "glad.h"
#include <iostream>
#include <stdexcept>

ShaderManager::ShaderManager() { _shaderManagerId = glCreateProgram(); }

ShaderManager::~ShaderManager() {}

void ShaderManager::addShader(Shader *shader)
{
	glAttachShader(_shaderManagerId, shader->getId());
	glLinkProgram(_shaderManagerId);
	delete shader;

	int  success;
	char infoLog[512];
	glGetProgramiv(_shaderManagerId, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(_shaderManagerId, 512, NULL, infoLog);
		throw std::runtime_error("Linking shader error\n");
	}
}

void ShaderManager::useShader() { glUseProgram(_shaderManagerId); }

void ShaderManager::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(_shaderManagerId, name.c_str()), (int)value);
	return;
}
void ShaderManager::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(_shaderManagerId, name.c_str()), value);
	return;
}
void ShaderManager::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(_shaderManagerId, name.c_str()), value);
	return;
}
void ShaderManager::setVec2(const std::string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(_shaderManagerId, name.c_str()), 1, &value[0]);
	return;
}
void ShaderManager::setVec2(const std::string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(_shaderManagerId, name.c_str()), x, y);
	return;
}
// ------------------------------------------------------------------------
void ShaderManager::setVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(_shaderManagerId, name.c_str()), 1, &value[0]);
	return;
}
void ShaderManager::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(_shaderManagerId, name.c_str()), x, y, z);
	return;
}
// ------------------------------------------------------------------------
void ShaderManager::setVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(_shaderManagerId, name.c_str()), 1, &value[0]);
	return;
}
void ShaderManager::setVec4(const std::string &name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(_shaderManagerId, name.c_str()), x, y, z, w);
	return;
}
// ------------------------------------------------------------------------
void ShaderManager::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(_shaderManagerId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	return;
}
// ------------------------------------------------------------------------
void ShaderManager::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(_shaderManagerId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	return;
}
// ------------------------------------------------------------------------
void ShaderManager::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(_shaderManagerId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	return;
}
