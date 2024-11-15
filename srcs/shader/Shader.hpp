#pragma once
#include <string>

class Shader {
      private:
	unsigned int _shaderId;
	std::string  _path;
	int	     _type;

      public:
	Shader(const std::string path, const int type);
	~Shader();

	unsigned int getId() const;
};
