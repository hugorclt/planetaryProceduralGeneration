#pragma once

#include "ShaderManager.hpp"
#include "quadtree/Quadtree.hpp"
#include "renderer/IRenderer.hpp"
#include <glm/glm.hpp>
#include <vector>

#define MINIMAL_VERTICES 128

class Terrain : public IRenderable {
      private:
	unsigned int		terrainId;
	std::vector<glm::vec3>	_vertices;
	QuadTreeNode	       *_root;
	std::vector<glm::uvec3> _lodIndices[6];
	ShaderManager		_shaderManager;
	unsigned int		_vao, _vbo;
	unsigned int		_ebo[6];

	void			_generateVertices();
	std::vector<glm::uvec3> _generateIndices(int gridSideLength, int step);
	void			_generateLodIndices();

      public:
	Terrain();

	std::vector<glm::uvec3> getIndices(int level) override;
	unsigned int		getVao() override;
	ShaderManager		getShaderManager() override;
	std::vector<glm::uvec3> getIndices() override;
};
