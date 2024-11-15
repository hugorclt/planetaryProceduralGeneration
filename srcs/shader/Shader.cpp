#include "Shader.hpp"
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <stdexcept>
#include <vector>
Shader::Shader(const std::string path, const int type) : _path(path), _type(type)
{
	std::cout << "Loading shader: " << path << std::endl;

	// Open the file
	std::ifstream ifs(path.c_str(), std::ios::in | std::ios::binary);
	if(!ifs)
	{
		throw std::runtime_error("Could not open shader file: " + path);
	}

	// Read file contents into a string
	std::string shaderCode((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	if(shaderCode.empty())
	{
		throw std::runtime_error("Shader file is empty: " + path);
	}

	// Debugging: print the shader code to confirm it's loaded correctly
	std::cout << "Shader code:\n" << shaderCode << std::endl;

	// Create shader
	_shaderId = glCreateShader(type);

	// Convert std::string to const char* for glShaderSource
	const char *shaderSource = shaderCode.c_str();
	glShaderSource(_shaderId, 1, &shaderSource, nullptr);

	// Compile shader
	glCompileShader(_shaderId);

	// Check for compilation errors
	int  success;
	char infoLog[512];
	glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(_shaderId, 512, nullptr, infoLog);
		std::string shaderType = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
		std::cerr << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		throw std::runtime_error("Shader::error\n");
	}
}

Shader::~Shader() { glDeleteShader(_shaderId); }

unsigned int Shader::getId() const { return _shaderId; }
