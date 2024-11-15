#include "Terrain.hpp"
#include "glad.h"

Terrain::Terrain()
{
	_shaderManager.addShader(new Shader("./shaders/shader.vert", GL_VERTEX_SHADER));
	_shaderManager.addShader(new Shader("./shaders/light.frag", GL_FRAGMENT_SHADER));

	_generateVertices();
	_generateLodIndices();

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(_vertices[0]), _vertices.data(), GL_STATIC_DRAW);

	for(int i = 0; i < 6; i++)
	{
		glGenBuffers(1, &(_ebo[i]));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _lodIndices[i].size() * sizeof(_lodIndices[i][0]), _lodIndices[i].data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Terrain::_generateVertices()
{
	int gridSideLength = MINIMAL_VERTICES - 1;
	int gridHalf = gridSideLength / 2;

	std::vector<glm::vec3>	vertices;
	std::vector<glm::uvec3> indices;

	for(int i = -gridHalf; i <= gridHalf; i++)
	{
		for(int j = -gridHalf; j <= gridHalf; j++)
		{
			_vertices.push_back(glm::vec3(j, 0.0f, i));
		}
	}
}

void Terrain::_generateLodIndices()
{
	for(int i = 0; i < 6; i++)
	{
		_lodIndices[i] = _generateIndices(MINIMAL_VERTICES - 1, i * 2);
	}
}

std::vector<glm::uvec3> Terrain::_generateIndices(int gridSideLength, int step)
{
	std::vector<glm::uvec3> indices;

	for(int j = 0; j < gridSideLength; j += step)
	{
		for(int i = 0; i < gridSideLength; i += step)
		{
			int row1 = j * (gridSideLength + 1);	      // Top row of the quad
			int row2 = (j + step) * (gridSideLength + 1); // Bottom row of the quad

			// Make sure we don't exceed the bounds
			if(j + step < gridSideLength && i + step < gridSideLength)
			{
				// Triangle 1
				indices.push_back(glm::uvec3(row1 + i, row1 + i + step, row2 + i + step));
				// Triangle 2
				indices.push_back(glm::uvec3(row1 + i, row2 + i + step, row2 + i));
			}
		}
	}

	return indices;
}

std::vector<glm::uvec3> Terrain::getIndices(int level) { return _lodIndices[level]; }
std::vector<glm::uvec3> Terrain::getIndices() { return _lodIndices[0]; }

unsigned int Terrain::getVao() { return _vao; }

ShaderManager Terrain::getShaderManager() { return _shaderManager; }
