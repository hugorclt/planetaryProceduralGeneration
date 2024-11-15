#pragma once

#include "ShaderManager.hpp"
#include <glm/glm.hpp>
#include <vector>

class IRenderable {
      public:
	// non-virtual interface
	// void fun() { do_fun(); } // equivalent to "this->do_fun()"

	// enable deletion of a Derived* through a Base*
	virtual ~IRenderable() = default;

      private:
	virtual std::vector<glm::uvec3> getIndices() = 0;
	virtual std::vector<glm::uvec3> getIndices(int level) = 0;
	virtual unsigned int		getVao() = 0;
	virtual ShaderManager		getShaderManager() = 0;
};
