#pragma once

#include "ShaderManager.hpp"
#include "renderer/IRenderer.hpp"
#include <glm/glm.hpp>
#include <vector>

class Object : public IRenderable {
      private:
	unsigned int		_objectId;
	std::vector<glm::vec3>	_vertices;
	std::vector<glm::uvec3> _indices;
	glm::vec3		_position = glm::vec3(0.0f, 0.0f, 0.0f);
	unsigned int		_vao, _vbo, _ebo;
	ShaderManager		_shaderManager;

      public:
	Object(std::vector<glm::vec3> vertices, std::vector<glm::uvec3> indices, ShaderManager shaderManager);
	Object(std::vector<glm::vec3> vertices, std::vector<glm::uvec3> indices, ShaderManager shaderManager, glm::vec3 pos);
	~Object();

	unsigned int		getVao() override;
	void			setPosition(glm::vec3 pos);
	glm::vec3		getPosition();
	std::vector<glm::uvec3> getIndices() override;
	ShaderManager		getShaderManager() override;
};
