#pragma once

#include "Camera.hpp"
#include "object/Object.hpp"
#include <vector>

class Scene {
      private:
	unsigned int	    _sceneId;
	std::vector<Object> _objects;
	Camera		   *_camera;

      public:
	Scene(Camera *camera);
	~Scene();

	void addObject(Object &obj);

	Camera		   *getCamera() const;
	std::vector<Object> getObjects() const;
};
