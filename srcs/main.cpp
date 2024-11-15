#include "camera/Camera.hpp"
#include "noise/Noise.hpp"
#include "renderer/Renderer.hpp"
#include "scene/Scene.hpp"
#include "shader/ShaderManager.hpp"
#include "terrain/Terrain.hpp"
#include <cstdlib>
#include <ctime>
#include <glad/glad.h>
#include <glm/ext/vector_uint3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// DON'T REMOVE THIS COMMENT

#include <GLFW/glfw3.h>
#include <iostream>

Object generatePlane()
{
	ShaderManager shaderManager;

	shaderManager.addShader(new Shader("./shaders/shader.vert", GL_VERTEX_SHADER));
	shaderManager.addShader(new Shader("./shaders/light.frag", GL_FRAGMENT_SHADER));

	// GRID
	int gridSideLength = 255;
	int gridHalf = gridSideLength / 2;

	std::vector<glm::vec3>	vertices;
	std::vector<glm::uvec3> indices;

	for(int i = -gridHalf; i <= gridHalf; i++)
	{
		for(int j = -gridHalf; j <= gridHalf; j++)
		{
			std::cout << "x: " << j << " z: " << i << std::endl;
			vertices.push_back(glm::vec3(j, 0.0f, i));
		}
	}

	for(int j = 0; j < gridSideLength; ++j)
	{
		for(int i = 0; i < gridSideLength; ++i)
		{
			int row1 = j * (gridSideLength + 1);
			int row2 = (j + 1) * (gridSideLength + 1);

			// triangle 1
			indices.push_back(glm::uvec3(row1 + i, row1 + i + 1, row2 + i + 1));

			// triangle 2
			indices.push_back(glm::uvec3(row1 + i, row2 + i + 1, row2 + i));
		}
	}

	// for(unsigned long i = 0; i < vertices.size(); i++)
	// {
	// 	float n = fractalBrownianMotion(vertices[i].x, vertices[i].z, 20);
	// 	n += 1.0;
	// 	n /= 2.0;
	//
	// 	vertices[i].y += n * 20;
	// }

	return Object(vertices, indices, shaderManager);
}

Object generateCube()
{
	ShaderManager shaderManager;

	shaderManager.addShader(new Shader("./shaders/shader.vert", GL_VERTEX_SHADER));
	shaderManager.addShader(new Shader("./shaders/lightSource.frag", GL_FRAGMENT_SHADER));

	// Vertex positions
	std::vector<glm::vec3> vertices = {// Back face
					   glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),

					   // Front face
					   glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f),

					   // Left face
					   glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 0.5f),

					   // Right face
					   glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.5f),

					   // Bottom face
					   glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f),

					   // Top face
					   glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f)};

	// Indices for each triangle (two per face)
	std::vector<glm::uvec3> indices = {// Back face
					   glm::uvec3(0, 1, 2), glm::uvec3(2, 3, 0),

					   // Front face
					   glm::uvec3(4, 5, 6), glm::uvec3(6, 7, 4),

					   // Left face
					   glm::uvec3(8, 9, 10), glm::uvec3(10, 11, 8),

					   // Right face
					   glm::uvec3(12, 13, 14), glm::uvec3(14, 15, 12),

					   // Bottom face
					   glm::uvec3(16, 17, 18), glm::uvec3(18, 19, 16),

					   // Top face
					   glm::uvec3(20, 21, 22), glm::uvec3(22, 23, 20)};

	return Object(vertices, indices, shaderManager, glm::vec3(0.0f, 20.0f, 0.0f));
}

int main()
{
	srand(time(NULL));

	Camera	*camera = new Camera();
	Renderer renderer;
	Scene	 scene(camera);

	renderer.setCamera(scene);

	// Object plane = generatePlane();
	// Object cube = generateCube();
	// scene.addObject(cube);
	// scene.addObject(plane);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Terrain *terrain = new Terrain();
	// scene.addObject(terrain);
	while(!renderer.shouldClose())
	{
		renderer.render(scene);
	}
	glfwTerminate();
	return 0;
}
